import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		text: "Read coils"
		onClicked: device.requestReadCoils(addressBox.value, amountBox.value)
	}

	Label {
		text: qsTr("Address:")
	}

	SpinBox {
		id: addressBox

		editable: true
		from: 0
		to: 65535
	}

	Label {
		text: qsTr("Amount:")
	}

	SpinBox {
		id: amountBox

		editable: true
		from: 0
		to: device.maxReadCoils
		value: 1
	}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
