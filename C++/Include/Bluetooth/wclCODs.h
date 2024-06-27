////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Wireless Communication Library 7                                         //
//                                                                            //
//   Copyright (C) 2006-2024 Mike Petrichenko                                 //
//                           Soft Service Company                             //
//                           All Rights Reserved                              //
//                                                                            //
//   http://www.btframework.com                                               //
//                                                                            //
//   support@btframework.com                                                  //
//   shop@btframework.com                                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace wclBluetooth
{
	#define COD_FORMAT_BIT_OFFSET		0
	#define COD_MINOR_BIT_OFFSET		2
	#define COD_MAJOR_BIT_OFFSET		(8 * 1)
	#define COD_SERVICE_BIT_OFFSET		(8 * 1 + 5)

	#define COD_FORMAT_MASK		0x000003
	#define COD_MINOR_MASK		0x0000FC
	#define COD_MAJOR_MASK		0x001F00
	#define COD_SERVICE_MASK	0xFFE000

	#define COD_VERSION			0x0

	/* Services class codes. */

	#define COD_SERVICE_LIMITED			0x0001
	#define COD_SERVICE_POSITIONING		0x0008
	#define COD_SERVICE_NETWORKING		0x0010
	#define COD_SERVICE_RENDERING		0x0020
	#define COD_SERVICE_CAPTURING		0x0040
	#define COD_SERVICE_OBJECT_XFER		0x0080
	#define COD_SERVICE_AUDIO			0x0100
	#define COD_SERVICE_TELEPHONY		0x0200
	#define COD_SERVICE_INFORMATION		0x0400

	#define COD_SERVICE_VALID_MASK	(COD_SERVICE_LIMITED | COD_SERVICE_POSITIONING | \
		COD_SERVICE_NETWORKING | COD_SERVICE_RENDERING | COD_SERVICE_CAPTURING | \
		COD_SERVICE_OBJECT_XFER | COD_SERVICE_AUDIO | COD_SERVICE_TELEPHONY | COD_SERVICE_INFORMATION)

	#define COD_SERVICE_MAX_COUNT	9

	/* Major class codes. */

	#define COD_MAJOR_MISCELLANEOUS		0x00
	#define COD_MAJOR_COMPUTER			0x01
	#define COD_MAJOR_PHONE				0x02
	#define COD_MAJOR_LAN_ACCESS		0x03
	#define COD_MAJOR_AUDIO				0x04
	#define COD_MAJOR_PERIPHERAL		0x05
	#define COD_MAJOR_IMAGING			0x06
	#define COD_MAJOR_WEARABLE			0x07
	#define COD_MAJOR_TOY				0x08
	#define COD_MAJOR_HEALTH			0x09
	#define COD_MAJOR_UNCLASSIFIED		0x1F

	/* Minor class codes specific to each major class. */

	#define COD_COMPUTER_MINOR_UNCLASSIFIED		0x00
	#define COD_COMPUTER_MINOR_DESKTOP			0x01
	#define COD_COMPUTER_MINOR_SERVER			0x02
	#define COD_COMPUTER_MINOR_LAPTOP			0x03
	#define COD_COMPUTER_MINOR_HANDHELD			0x04
	#define COD_COMPUTER_MINOR_PALM				0x05
	#define COD_COMPUTER_MINOR_WEARABLE			0x06

	#define COD_PHONE_MINOR_UNCLASSIFIED		0x00
	#define COD_PHONE_MINOR_CELLULAR			0x01
	#define COD_PHONE_MINOR_CORDLESS			0x02
	#define COD_PHONE_MINOR_SMART				0x03
	#define COD_PHONE_MINOR_WIRED_MODEM			0x04

	#define COD_AUDIO_MINOR_UNCLASSIFIED				0x00
	#define COD_AUDIO_MINOR_HEADSET						0x01
	#define COD_AUDIO_MINOR_HANDS_FREE					0x02
	#define COD_AUDIO_MINOR_HEADSET_HANDS_FREE			0x03
	#define COD_AUDIO_MINOR_MICROPHONE					0x04
	#define COD_AUDIO_MINOR_LOUDSPEAKER					0x05
	#define COD_AUDIO_MINOR_HEADPHONES					0x06
	#define COD_AUDIO_MINOR_PORTABLE_AUDIO				0x07
	#define COD_AUDIO_MINOR_CAR_AUDIO					0x08
	#define COD_AUDIO_MINOR_SET_TOP_BOX					0x09
	#define COD_AUDIO_MINOR_HIFI_AUDIO					0x0A
	#define COD_AUDIO_MINOR_VCR							0x0B
	#define COD_AUDIO_MINOR_VIDEO_CAMERA				0x0C
	#define COD_AUDIO_MINOR_CAMCORDER					0x0D
	#define COD_AUDIO_MINOR_VIDEO_MONITOR				0x0E
	#define COD_AUDIO_MINOR_VIDEO_DISPLAY_LOUDSPEAKER	0x0F
	#define COD_AUDIO_MINOR_VIDEO_DISPLAY_CONFERENCING	0x10
	#define COD_AUDIO_MINOR_GAMING_TOY					0x12

	#define COD_PERIPHERAL_MINOR_KEYBOARD_MASK	0x10
	#define COD_PERIPHERAL_MINOR_POINTER_MASK	0x20

	#define COD_PERIPHERAL_MINOR_NO_CATEGORY		0x00
	#define COD_PERIPHERAL_MINOR_JOYSTICK			0x01
	#define COD_PERIPHERAL_MINOR_GAMEPAD			0x02
	#define COD_PERIPHERAL_MINOR_REMOTE_CONTROL		0x03
	#define COD_PERIPHERAL_MINOR_SENSING			0x04

	#define COD_IMAGING_MINOR_DISPLAY_MASK	0x04
	#define COD_IMAGING_MINOR_CAMERA_MASK	0x08
	#define COD_IMAGING_MINOR_SCANNER_MASK	0x10
	#define COD_IMAGING_MINOR_PRINTER_MASK	0x20

	#define COD_WEARABLE_MINOR_WRIST_WATCH	0x01
	#define COD_WEARABLE_MINOR_PAGER		0x02
	#define COD_WEARABLE_MINOR_JACKET		0x03
	#define COD_WEARABLE_MINOR_HELMET		0x04
	#define COD_WEARABLE_MINOR_GLASSES		0x05

	#define COD_TOY_MINOR_ROBOT					0x01
	#define COD_TOY_MINOR_VEHICLE				0x02
	#define COD_TOY_MINOR_DOLL_ACTION_FIGURE	0x03
	#define COD_TOY_MINOR_CONTROLLER			0x04
	#define COD_TOY_MINOR_GAME					0x05

	#define COD_HEALTH_MINOR_BLOOD_PRESSURE_MONITOR	0x01
	#define COD_HEALTH_MINOR_THERMOMETER			0x02
	#define COD_HEALTH_MINOR_WEIGHING_SCALE			0x03
	#define COD_HEALTH_MINOR_GLUCOSE_METER			0x04
	#define COD_HEALTH_MINOR_PULSE_OXIMETER			0x05
	#define COD_HEALTH_MINOR_HEART_PULSE_MONITOR	0x06
	#define COD_HEALTH_MINOR_HEALTH_DATA_DISPLAY	0x07
	#define COD_HEALTH_MINOR_STEP_COUNTER			0x08

	#define COD_LAN_ACCESS_BIT_OFFSET	5

	#define COD_LAN_MINOR_MASK		0x00001C
	#define COD_LAN_ACCESS_MASK		0x0000E0

	/* LAN access percent usage subcodes. */

	#define COD_LAN_MINOR_UNCLASSIFIED	0x00

	#define COD_LAN_ACCESS_0_USED	0x00
	#define COD_LAN_ACCESS_17_USED	0x01
	#define COD_LAN_ACCESS_33_USED	0x02
	#define COD_LAN_ACCESS_50_USED	0x03
	#define COD_LAN_ACCESS_67_USED	0x04
	#define COD_LAN_ACCESS_83_USED	0x05
	#define COD_LAN_ACCESS_99_USED	0x06
	#define COD_LAN_ACCESS_FULL		0x07
}