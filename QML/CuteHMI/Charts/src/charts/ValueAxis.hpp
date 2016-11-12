#ifndef CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_VALUEAXIS_HPP
#define CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_VALUEAXIS_HPP

#include "PlotArea.hpp"

#include <QQuickPaintedItem>

namespace cutehmi {
namespace charts {

/**
 * Value axis.
 *
 * @todo use QSG* and subclass QQuickItem if possible instead of QQuickPaintedItem.
 */
class ValueAxis:
		public QQuickPaintedItem
{
	Q_OBJECT

	public:
		static constexpr qreal INITIAL_FROM = 0.0;
		static constexpr qreal INITIAL_TO = 100.0;

		Q_PROPERTY(qreal from READ from WRITE setFrom NOTIFY fromChanged)
		Q_PROPERTY(qreal to READ to WRITE setTo NOTIFY toChanged)
		Q_PROPERTY(PlotArea * plotArea READ plotArea WRITE setPlotArea NOTIFY plotAreaChanged)

		ValueAxis(QQuickItem * parent = 0);

		qreal from() const;

		void setFrom(qreal from);

		qreal to() const;

		void setTo(qreal to);

		PlotArea * plotArea() const;

		void setPlotArea(PlotArea * plotArea);

		virtual qreal mapToPlotArea(qreal value) const = 0;

//		virtual bool contentContains(qreal point) const = 0;

	signals:
		void fromChanged();

		void toChanged();

		void plotAreaChanged(PlotArea * oldPlotArea);

	protected:
		qreal left() const;

		qreal right() const;

		qreal top() const;

		qreal bottom() const;

		qreal plotAreaWidth() const;

		qreal plotAreaHeight() const;

	private:
		qreal m_from;
		qreal m_to;
		PlotArea * m_plotArea;
};

}
}

#endif
