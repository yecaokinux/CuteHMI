#ifndef INCLUDECUTEHMIMODBUSINTERNALTCPSERVERCONFIG_HPP
#define INCLUDECUTEHMIMODBUSINTERNALTCPSERVERCONFIG_HPP

#include "Config.hpp"

#include <QObject>
#include <QString>
#include <QReadWriteLock>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE TCPServerConfig:
	public Config
{
		Q_OBJECT

	public:
		typedef std::pair<quint16, quint16> AddressRange;

		static constexpr int MIN_SLAVE_ADDRESS = 1; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static constexpr int MAX_SLAVE_ADDRESS = 247; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static constexpr const char * INITIAL_HOST = "localhost";
		static constexpr int INITIAL_PORT = 502;
		static constexpr int INITIAL_SLAVE_ADDRESS = MIN_SLAVE_ADDRESS;
		static constexpr quint16 INITIAL_COILS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_COILS_ADDRESS_RANGE_MAX = 65535;
		static constexpr quint16 INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX = 65535;
		static constexpr quint16 INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX = 65535;
		static constexpr quint16 INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX = 65535;

		explicit TCPServerConfig(QObject * parent = nullptr);

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		int slaveAddress() const;

		void setSlaveAddress(int address);

		AddressRange coilsAddressRange() const;

		void setCoilsAddressRange(AddressRange addressRange);

		AddressRange inputRegistersAddressRange() const;

		void setInputRegistersAddressRange(AddressRange addressRange);

		AddressRange discreteInputsAddressRange() const;

		void setDiscreteInputsAddressRange(AddressRange addressRange);

		AddressRange holdingRegistersAddressRange() const;

		void setHoldingRegistersAddressRange(AddressRange addressRange);

	private:
		struct Members
		{
			QString host = INITIAL_HOST;
			int	port = INITIAL_PORT;
			int slaveAddress = INITIAL_SLAVE_ADDRESS;
			AddressRange coilsAddressRange = AddressRange(INITIAL_COILS_ADDRESS_RANGE_MIN, INITIAL_COILS_ADDRESS_RANGE_MAX);
			AddressRange discreteInputsAddressRange = AddressRange(INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN, INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX);
			AddressRange holdingRegistersAddressRange = AddressRange(INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN, INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX);
			AddressRange inputRegistersAddressRange = AddressRange(INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN, INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX);
			mutable QReadWriteLock lock;
		};

		MPtr<Members> m;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALTCPSERVERCONFIG_HPP
