#include <cutehmi/dataacquisition/internal/TagCache.hpp>

#include <QSqlRecord>
#include <QSqlResult>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

TagCache::TagCache(Schema * schema, QObject * parent):
	TableObject(schema, parent),
	m(new Members)
{
}

int TagCache::getId(const QString & name, QSqlDatabase & db)
{
	TagIdContainter::const_iterator tag;
	TagIdContainter::const_iterator tagIdsEnd;
	bool tagIdsEmpty;

	// Access to m->tagIds is a critical section.
	{
		QReadLocker locker(& m->tagIdsLock);
		tag = m->tagIds.find(name);
		tagIdsEnd = m->tagIds.end();
		tagIdsEmpty = m->tagIds.empty();
	}

	if (tag == tagIdsEnd) {
		// If tag ids map is empty update it from database.
		if (tagIdsEmpty) {
			update(db);
			{
				QReadLocker locker(& m->tagIdsLock);
				tag = m->tagIds.find(name);
				tagIdsEnd = m->tagIds.end();
			}
		}

		// If tag wasn't found it probably does not exist in database, so insert it.
		if (tag == tagIdsEnd) {
			insert(name, db);
			{
				QReadLocker locker(& m->tagIdsLock);
				tag = m->tagIds.find(name);
				tagIdsEnd = m->tagIds.end();
			}

			// If insert query fails, then some other thread might have inserted it.
			if (tag == tagIdsEnd) {
				update(db);
				{
					QReadLocker locker(& m->tagIdsLock);
					tag = m->tagIds.find(name);
				}
			}
		}

		processErrors();
	}

	return tag.value();
}

void TagCache::insert(const QString & name, QSqlDatabase & db)
{
	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		CUTEHMI_DEBUG("Inserting '" << name << "' tag...");

		query.prepare(QString("INSERT INTO %1.tag (name) VALUES (:name) RETURNING id").arg(schema()->name()));
		query.bindValue(":name", name);
		query.exec();
		int idIndex = query.record().indexOf("id");

		if (query.first()) {
			QWriteLocker locker(& m->tagIdsLock);
			m->tagIds[name] = query.value(idIndex).toInt();
		}
		pushError(query.lastError());
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		CUTEHMI_DEBUG("Inserting '" << name << "' tag...");

		query.prepare(QString("INSERT INTO [%1.tag] (name) VALUES (:name);").arg(schema()->name()));
		query.bindValue(":name", name);
		query.exec();
		query.finish();


		query.prepare(QString("SELECT * FROM [%1.tag] WHERE name = :name").arg(schema()->name()));
		query.bindValue(":name", name);
		query.exec();
		int idIndex = query.record().indexOf("id");
		if (query.first()) {
			QWriteLocker locker(& m->tagIdsLock);
			m->tagIds[name] = query.value(idIndex).toInt();
		}
		pushError(query.lastError());
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
}

void TagCache::update(QSqlDatabase & db)
{

	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		CUTEHMI_DEBUG("Updating tag cache...");

		query.exec(QString("SELECT * FROM %1.tag").arg(schema()->name()));
		int idIndex = query.record().indexOf("id");
		int nameIndex = query.record().indexOf("name");
		{
			QWriteLocker locker(& m->tagIdsLock);

			m->tagIds.clear();
			while (query.next())
				m->tagIds[query.value(nameIndex).toString()] = query.value(idIndex).toInt();
		}
		pushError(query.lastError());
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		CUTEHMI_DEBUG("Updating tag cache...");

		query.exec(QString("SELECT * FROM [%1.tag]").arg(schema()->name()));
		int idIndex = query.record().indexOf("id");
		int nameIndex = query.record().indexOf("name");
		{
			QWriteLocker locker(& m->tagIdsLock);

			m->tagIds.clear();
			while (query.next())
				m->tagIds[query.value(nameIndex).toString()] = query.value(idIndex).toInt();
		}
		pushError(query.lastError());
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
}

}
}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
