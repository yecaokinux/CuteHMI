#ifndef INCLUDECUTEHMISERVICESSERVICEABLE_HPP
#define INCLUDECUTEHMISERVICESSERVICEABLE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QState>
#include <QSignalTransition>

namespace cutehmi {
namespace services {

/**
 * Serviceable interface.
 */
class CUTEHMI_SERVICES_API Serviceable
{
	public:
		typedef QHash<QState *, QString> ServiceStatuses;

		Serviceable() = default;

		/**
		 * Configure started state. Started state is not directly accessible. Intead its child states shall be configured.
		 * @param active active state.
		 * @param idling idling state.
		 * @param yielding yielding state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureStarted(QState * active, const QState * idling, const QState * yielding) = 0;

		/**
		 * Configure starting state.
		 * @param starting state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureStarting(QState * starting) = 0;

		/**
		 * Configure stopping state.
		 * @param stopping state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureStopping(QState * stopping) = 0;

		/**
		 * Configure broken state.
		 * @param broken state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureBroken(QState * broken) = 0;

		/**
		 * Configure repairing state.
		 * @param repairing state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureRepairing(QState * repairing) = 0;

		/**
		 * Transition to started state.
		 * @return transition to started state. It is allowed to return @p nullptr. In such case transition from starting to
		 * started state will be immediate.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToStarted() const = 0;

		/**
		 * Transition to stopped state.
		 * @return transition to stopped state. It is allowed to return @p nullptr. In such case transition from stopping to
		 * stopped state will be immediate.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToStopped() const = 0;

		/**
		 * Transition to broken state.
		 * @return transition to broken state. It is allowed to return @p nullptr. In such case service will never enter broken
		 * or repairing states.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToBroken() const = 0;

		/**
		 * Transition to yielding state.
		 * @return transition to yielding state. It is allowed to return @p nullptr. In such case service will skip yielding
		 * state and immediately become active. This will make service impolite.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToYielding() const = 0;

		/**
		 * Transition to idling state.
		 * @return transition to idling state. It is allowed to return @p nullptr. In such case service will not enter idling
		 * state and will remain persistently active. This will make service impolite.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToIdling() const = 0;

	protected:
		virtual ~Serviceable() = default;

		Serviceable(const Serviceable & other) = default;

		Serviceable & operator =(const Serviceable & other) = default;
};

}
}

Q_DECLARE_METATYPE(cutehmi::services::Serviceable *)

#endif // INCLUDECUTEHMISERVICESSERVICEABLE_HPP