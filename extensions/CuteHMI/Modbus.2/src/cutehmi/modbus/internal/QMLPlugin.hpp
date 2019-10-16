#ifndef H_QML_CUTEHMI_MODBUS_SRC_CUTEHMIMODBUS2QMLPLUGIN_HPP
#define H_QML_CUTEHMI_MODBUS_SRC_CUTEHMIMODBUS2QMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

namespace cutehmi {
namespace modbus {
namespace internal {

class QMLPlugin:
	public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

	public:
		void registerTypes(const char * uri) override;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
