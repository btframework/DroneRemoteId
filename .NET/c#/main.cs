using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

using wclCommon;
using wclWiFi;
using wclWiFi.Dri;

namespace DroneRemoteIdCSharp
{
    public partial class fmMain : Form
    {
        private wclWiFiClient WiFiClient;
        private wclWiFiEvents WiFiEvents;

        private Guid FId;
        private wclWiFiDriParser FParser;
        private TreeNode FRootNode;
        private Boolean FScanActive;

        private void Trace(String Msg)
        {
            lbLog.Items.Add(Msg);
            lbLog.TopIndex = lbLog.Items.Count - 1;
        }

        private void Trace(String Msg, Int32 Res)
        {
            Trace(Msg + ": 0x" + Res.ToString("X8"));
        }

        private void AdapterDisabled()
        {
            StopScan();
            FId = Guid.Empty;

            btStart.Enabled = false;
            btStop.Enabled = false;
        }

        private void ClearMessageDetails()
        {
            lvDetails.Items.Clear();
        }

        private void EnumInterfaces()
        {
            btStart.Enabled = false;
            btStop.Enabled = false;

            wclWiFiInterfaceData[] Ifaces;
            Int32 Res = WiFiClient.EnumInterfaces(out Ifaces);
            if (Res != wclErrors.WCL_E_SUCCESS)
                Trace("Enum interfaces failed", Res);
            else
            {
                if (Ifaces == null || Ifaces.Length == 0)
                    Trace("No one WiFi interface found");
                else
                {
                    Boolean Found = false;
                    foreach (wclWiFiInterfaceData Data in Ifaces)
                    {
                        wclWiFiInterface Iface = new wclWiFiInterface(Data.Id);
                        if (Iface.Open() == wclErrors.WCL_E_SUCCESS)
                        {
                            wclWiFiPhyRadioState[] States;
                            Res = Iface.GetRadioState(out States);
                            if (Res == wclErrors.WCL_E_SUCCESS)
                            {
                                if (States != null && States.Length > 0)
                                {
                                    Boolean Enabled = false;
                                    foreach (wclWiFiPhyRadioState State in States)
                                    {
                                        Enabled = (State.SoftwareState == wclWiFiRadioState.rsOn &&
                                            State.HardwareState == wclWiFiRadioState.rsOn);
                                        if (!Enabled)
                                            break;
                                    }
                                    Found = Enabled;
                                }
                            }

                            if (Found)
                                FId = Iface.Id;
                            Iface.Close();
                        }

                        if (Found)
                            break;
                    }

                    if (Found)
                    {
                        Trace("Use WiFi interface " + FId.ToString());

                        btStart.Enabled = true;
                        btStop.Enabled = false;
                    }
                }
            }
        }

        private TreeNode FindDrone(String Ssid)
        {
            TreeNode Result = null;

            if (FRootNode.Nodes.Count > 0)
            {
                foreach (TreeNode DroneNode in FRootNode.Nodes)
                {
                    if (DroneNode.Text == Ssid)
                    {
                        Result = DroneNode;
                        break;
                    }
                }
            }

            if (Result == null)
            {
                Result = FRootNode.Nodes.Add(Ssid);
                FRootNode.ExpandAll();
            }
            return Result;
        }

        private String MessageTypeToText(wclWiFiDriAsdMessage Message)
        {
            switch (Message.MessageType)
            {
                case wclWiFiDriAsdMessageType.mtBasicId:
                    return "BASIC ID";
                case wclWiFiDriAsdMessageType.mtLocation:
                    return "LOCATION";
                case wclWiFiDriAsdMessageType.mtAuth:
                    return "AUTH";
                case wclWiFiDriAsdMessageType.mtSelfId:
                    return "SELF ID";
                case wclWiFiDriAsdMessageType.mtSystem:
                    return "SYSTEM";
                case wclWiFiDriAsdMessageType.mtOperatorId:
                    return "OPERATOR ID";
                default:
                    return "UNKNOWN";
            }
        }

        private String AsdVerticalAccuracyToText(wclWiFiDriAsdUavVerticalAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclWiFiDriAsdUavVerticalAccuracy.vaUnknown:
                    return "Unknow";
                case wclWiFiDriAsdUavVerticalAccuracy.va150M:
                    return "150 m";
                case wclWiFiDriAsdUavVerticalAccuracy.va45M:
                    return "45 m";
                case wclWiFiDriAsdUavVerticalAccuracy.va25M:
                    return "25 m";
                case wclWiFiDriAsdUavVerticalAccuracy.va10M:
                    return "10 m";
                case wclWiFiDriAsdUavVerticalAccuracy.va3M:
                    return "3 m";
                case wclWiFiDriAsdUavVerticalAccuracy.va1M:
                    return "1 m";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdHeightReferenceToText(wclWiFiDriAsdUavHeightReference Reference)
        {
            switch (Reference)
            {
                case wclWiFiDriAsdUavHeightReference.hrTakeOff:
                    return "Take off";
                case wclWiFiDriAsdUavHeightReference.hrGround:
                    return "Ground";
                default:
                    return "Raw value: 0x" + ((Byte)Reference).ToString("X2");
            }
        }

        private String AsdHorizontalAccuracyToText(wclWiFiDriAsdUavHorizontalAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclWiFiDriAsdUavHorizontalAccuracy.haUnknown:
                    return "Unknown";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha10Nm:
                    return "10 miles";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha4Nm:
                    return "4 miles";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha2Nm:
                    return "2 miles";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha1Nm:
                    return "1 mile";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha05Nm:
                    return "0.5 mile";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha03Nm:
                    return "0.3 mile";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha01Nm:
                    return "0.1 mile";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha005Nm:
                    return "0.05 mile";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha30M:
                    return "30 meters";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha10M:
                    return "10 meters";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha3M:
                    return "3 meters";
                case wclWiFiDriAsdUavHorizontalAccuracy.ha1M:
                    return "1 meter";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdSpeedAccuracyToText(wclWiFiDriAsdUavSpeedAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclWiFiDriAsdUavSpeedAccuracy.saUnknown:
                    return "Unknown";
                case wclWiFiDriAsdUavSpeedAccuracy.sa10MS:
                    return "10 m/s";
                case wclWiFiDriAsdUavSpeedAccuracy.sa3MS:
                    return "3 m/s";
                case wclWiFiDriAsdUavSpeedAccuracy.sa1Ms:
                    return "1 m/s";
                case wclWiFiDriAsdUavSpeedAccuracy.sa03Ms:
                    return "0.3 m/s";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdStatusToText(wclWiFiDriAsdUavStatus Status)
        {
            switch (Status)
            {
                case wclWiFiDriAsdUavStatus.usUndeclared:
                    return "Undeclared";
                case wclWiFiDriAsdUavStatus.usGround:
                    return "Ground";
                case wclWiFiDriAsdUavStatus.usAirborne:
                    return "Airborne";
                case wclWiFiDriAsdUavStatus.usEmergency:
                    return "Emergency";
                case wclWiFiDriAsdUavStatus.usFailure:
                    return "Failure";
                default:
                    return "Raw value: 0x" + ((Byte)Status).ToString("X2");
            }
        }

        private String AsdTimestampAccuracyToText(wclWiFiDriAsdUavTimestampAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclWiFiDriAsdUavTimestampAccuracy.taUnknown:
                    return "Unknown";
                case wclWiFiDriAsdUavTimestampAccuracy.ta01s:
                    return "0.1 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta02s:
                    return "0.2 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta03s:
                    return "0.3 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta04s:
                    return "0.4 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta05s:
                    return "0.5 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta06s:
                    return "0.6 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta07s:
                    return "0.7 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta08s:
                    return "0.8 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta09s:
                    return "0.9 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta1s:
                    return "1 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta11s:
                    return "1.1 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta12s:
                    return "1.2 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta13s:
                    return "1.3 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta14s:
                    return "1.4 second";
                case wclWiFiDriAsdUavTimestampAccuracy.ta15s:
                    return "1.5 second";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdAltitudeToText(Single Altitude)
        {
            if (Altitude == -1000)
                return "Invalid";
            return Altitude.ToString();
        }

        private String AsdDescriptionTypeToText(wclWiFiDriAsdDescriptionType DescriptionType)
        {
            switch (DescriptionType)
            {
                case wclWiFiDriAsdDescriptionType.dtText:
                    return "Text";
                case wclWiFiDriAsdDescriptionType.dtEmergency:
                    return "Emergency";
                case wclWiFiDriAsdDescriptionType.dtExtended:
                    return "Extended";
                default:
                    return "Raw value: 0x" + ((Byte)DescriptionType).ToString("X2");
            }
        }

        private String AsdDirectionToText(UInt16 Direction)
        {
            if (Direction > 360)
                return "Invalid";
            return Direction.ToString();
        }

        private String AsdHorizontalSpeedToText(Single Speed)
        {
            if (Speed == 255)
                return "Invalid";
            return Speed.ToString();
        }

        private String AsdLatLonToText(Double LatLon)
        {
            if (LatLon == 0)
                return "Invalid";
            return LatLon.ToString();
        }

        private String AsdOperatorClassificationToText(wclWiDiDriAsdOperatorClassification Classification)
        {
            switch (Classification)
            {
                case wclWiDiDriAsdOperatorClassification.ocUndeclared:
                    return "Undeclared";
                case wclWiDiDriAsdOperatorClassification.ocEu:
                    return "EU";
                default:
                    return "Raw value: 0x" + ((Byte)Classification).ToString("X2");
            }
        }

        private String AsdLocationTypeToText(wclWiDiDriAsdOperatorLocationType Location)
        {
            switch (Location)
            {
                case wclWiDiDriAsdOperatorLocationType.ltTakeOff:
                    return "Take off";
                case wclWiDiDriAsdOperatorLocationType.ltLiveGnss:
                    return "Live GNSS";
                case wclWiDiDriAsdOperatorLocationType.ltFixed:
                    return "Fixed";
                default:
                    return "Raw value: 0x" + ((Byte)Location).ToString("X2");
            }
        }

        private String AsdEuUavCategoryToText(wclWiDiDriAsdUavEuCategory Category)
        {
            switch (Category)
            {
                case wclWiDiDriAsdUavEuCategory.ucUndeclared:
                    return "Undeclared";
                case wclWiDiDriAsdUavEuCategory.ucOpen:
                    return "Open";
                case wclWiDiDriAsdUavEuCategory.ucSpecific:
                    return "Specific";
                case wclWiDiDriAsdUavEuCategory.ucCertified:
                    return "Certified";
                default:
                    return "Raw value: 0x" + ((Byte)Category).ToString("X2");
            }
        }

        private String AsdEuUavClassToText(wclWiDiDriAsdUavEuClass UavClass)
        {
            switch (UavClass)
            {
                case wclWiDiDriAsdUavEuClass.ucUnspecified:
                    return "Unspecified";
                case wclWiDiDriAsdUavEuClass.ucClass0:
                    return "Class 0";
                case wclWiDiDriAsdUavEuClass.ucClass1:
                    return "Class 1";
                case wclWiDiDriAsdUavEuClass.ucClass2:
                    return "Class 2";
                case wclWiDiDriAsdUavEuClass.ucClass3:
                    return "Class 3";
                case wclWiDiDriAsdUavEuClass.ucClass4:
                    return "Class 4";
                case wclWiDiDriAsdUavEuClass.ucClass5:
                    return "Class 5";
                case wclWiDiDriAsdUavEuClass.ucClass6:
                    return "Class 6";
                default:
                    return "Raw value: 0x" + ((Byte)UavClass).ToString("X2");
            }
        }

        private String AsdIdTypeToText(wclWiFiDriAsdIdType IdType)
        {
            switch (IdType)
            {
                case wclWiFiDriAsdIdType.itNone:
                    return "None";
                case wclWiFiDriAsdIdType.itSerialNumber:
                    return "Serial number";
                case wclWiFiDriAsdIdType.itCaaRegistrationId:
                    return "CAA registration ID";
                case wclWiFiDriAsdIdType.itUtmAssignedUuid:
                    return "UTM assigned UUID";
                case wclWiFiDriAsdIdType.itSpecificSessionId:
                    return "Specific session ID";
                default:
                    return "Raw value: 0x" + ((Byte)IdType).ToString("X2");
            }
        }

        private String AsdUavTypeToText(wclWiFiDriAsdUavType UavType)
        {
            switch (UavType)
            {
                case wclWiFiDriAsdUavType.utNone:
                    return "None";
                case wclWiFiDriAsdUavType.utAeroplane:
                    return "Aeroplane";
                case wclWiFiDriAsdUavType.utCopter:
                    return "Copter";
                case wclWiFiDriAsdUavType.utGyroplane:
                    return "Gyroplane";
                case wclWiFiDriAsdUavType.utHybridLift:
                    return "Hybrid";
                case wclWiFiDriAsdUavType.utOrnithopter:
                    return "Ornithopter";
                case wclWiFiDriAsdUavType.utGlider:
                    return "Glider";
                case wclWiFiDriAsdUavType.utKite:
                    return "Kite";
                case wclWiFiDriAsdUavType.utFreeBalloon:
                    return "Free balloon";
                case wclWiFiDriAsdUavType.utCaptiveBalloon:
                    return "Captive balloon";
                case wclWiFiDriAsdUavType.utAirship:
                    return "Airship";
                case wclWiFiDriAsdUavType.utFreeFallParachute:
                    return "Free fall parachute";
                case wclWiFiDriAsdUavType.utRocket:
                    return "Rocket";
                case wclWiFiDriAsdUavType.utTetheredPoweredAircraft:
                    return "Tethered powered aircraft";
                case wclWiFiDriAsdUavType.utGroundObstacle:
                    return "Ground obstacle";
                default:
                    return "Raw value: 0x" + ((Byte)UavType).ToString("X2");
            }
        }

        private void ShowAsdLocationMessage(wclWiFiDriAsdLocationMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("Baro Altitude");
            Item.SubItems.Add(AsdAltitudeToText(Message.BaroAltitude));

            Item = lvDetails.Items.Add("Baro Accuracy");
            Item.SubItems.Add(AsdVerticalAccuracyToText(Message.BaroAccuracy));

            Item = lvDetails.Items.Add("Direction");
            Item.SubItems.Add(AsdDirectionToText(Message.Direction));

            Item = lvDetails.Items.Add("Geo Altitude");
            Item.SubItems.Add(AsdAltitudeToText(Message.GeoAltitude));

            Item = lvDetails.Items.Add("Height");
            Item.SubItems.Add(AsdAltitudeToText(Message.Height));

            Item = lvDetails.Items.Add("Height Reference");
            Item.SubItems.Add(AsdHeightReferenceToText(Message.HeightReference));

            Item = lvDetails.Items.Add("Horizontal Accuracy");
            Item.SubItems.Add(AsdHorizontalAccuracyToText(Message.HorizontalAccuracy));

            Item = lvDetails.Items.Add("Horizontal Speed");
            Item.SubItems.Add(AsdHorizontalSpeedToText(Message.HorizontalSpeed));

            Item = lvDetails.Items.Add("Latitude");
            Item.SubItems.Add(AsdLatLonToText(Message.Latitude));

            Item = lvDetails.Items.Add("Longitude");
            Item.SubItems.Add(AsdLatLonToText(Message.Longitude));

            Item = lvDetails.Items.Add("Speed Accuracy");
            Item.SubItems.Add(AsdSpeedAccuracyToText(Message.SpeedAccuracy));

            Item = lvDetails.Items.Add("Status");
            Item.SubItems.Add(AsdStatusToText(Message.Status));

            Item = lvDetails.Items.Add("Timestamp");
            Item.SubItems.Add(Message.Timestamp.ToString());

            Item = lvDetails.Items.Add("Timestamp Accuracy");
            Item.SubItems.Add(AsdTimestampAccuracyToText(Message.TimestampAccuracy));

            Item = lvDetails.Items.Add("Vertical Accuracy");
            Item.SubItems.Add(AsdVerticalAccuracyToText(Message.VerticalAccuracy));

            Item = lvDetails.Items.Add("Vertical Speed");
            Item.SubItems.Add(Message.VerticalSpeed.ToString());
        }

        private void ShowAsdSelfIdMessage(wclWiFiDriAsdSelfIdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("Description");
            Item.SubItems.Add(Message.Description);

            Item = lvDetails.Items.Add("Description Type");
            Item.SubItems.Add(AsdDescriptionTypeToText(Message.DescriptionType));
        }

        private void ShowAsdOperatorIdMessage(wclWiFiDriAsdOperatorIdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("ID");
            Item.SubItems.Add(Encoding.ASCII.GetString(Message.Id));

            Item = lvDetails.Items.Add("ID Type");
            Item.SubItems.Add("0x" + Message.IdType.ToString("X2"));
        }

        private void ShowAsdSystemMessage(wclWiFiDriAsdSystemMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("Area ceiling");
            Item.SubItems.Add(AsdAltitudeToText(Message.AreaCeiling));

            Item = lvDetails.Items.Add("Area count");
            Item.SubItems.Add(Message.AreaCount.ToString());

            Item = lvDetails.Items.Add("Area floor");
            Item.SubItems.Add(AsdAltitudeToText(Message.AreaFloor));

            Item = lvDetails.Items.Add("Area radius");
            Item.SubItems.Add(Message.AreaRadius.ToString());

            Item = lvDetails.Items.Add("Operator altitude");
            Item.SubItems.Add(Message.OperatorAltitude.ToString());

            Item = lvDetails.Items.Add("Operator classification");
            Item.SubItems.Add(AsdOperatorClassificationToText(Message.OperatorClassification));

            Item = lvDetails.Items.Add("Operator latitude");
            Item.SubItems.Add(AsdLatLonToText(Message.OperatorLatitude));

            Item = lvDetails.Items.Add("Operator latitude");
            Item.SubItems.Add(AsdLatLonToText(Message.OperatorLatitude));

            Item = lvDetails.Items.Add("Operator longitude");
            Item.SubItems.Add(AsdLatLonToText(Message.OperatorLongitude));

            Item = lvDetails.Items.Add("Location type");
            Item.SubItems.Add(AsdLocationTypeToText(Message.OperatorLocation));

            Item = lvDetails.Items.Add("Timestamp");
            Item.SubItems.Add(Message.Timestamp.ToString());

            Item = lvDetails.Items.Add("UAV EU category");
            Item.SubItems.Add(AsdEuUavCategoryToText(Message.UavEuCategory));

            Item = lvDetails.Items.Add("UAV EU class");
            Item.SubItems.Add(AsdEuUavClassToText(Message.UavEuClass));
        }

        private void ShowAsdBassicIdMessage(wclWiFiDriAsdBasicIdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("ID");
            Item.SubItems.Add(Encoding.ASCII.GetString(Message.Id));

            Item = lvDetails.Items.Add("ID type");
            Item.SubItems.Add(AsdIdTypeToText(Message.IdType));

            Item = lvDetails.Items.Add("ID type");
            Item.SubItems.Add(AsdUavTypeToText(Message.UavType));
        }

        private void ShowUnknownAsdMessage(wclWiFiDriAsdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("Message type");
            Item.SubItems.Add(((Byte)Message.MessageType).ToString("X2"));

            String Str = "";
            if (Message.Data != null && Message.Data.Length > 0)
            {
                foreach (Byte b in Message.Data)
                    Str = Str + b.ToString("X2");
            }
            Item = lvDetails.Items.Add("Raw date");
            Item.SubItems.Add(Str);
        }

        private void UpdateAsdMessageDetails(String Ssid, wclWiFiDriAsdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("SSID");
            Item.SubItems.Add(Ssid);

            Item = lvDetails.Items.Add("");
            Item.SubItems.Add("");

            switch (Message.MessageType)
            {
                case wclWiFiDriAsdMessageType.mtBasicId:
                    ShowAsdBassicIdMessage((wclWiFiDriAsdBasicIdMessage)Message);
                    break;
                case wclWiFiDriAsdMessageType.mtLocation:
                    ShowAsdLocationMessage((wclWiFiDriAsdLocationMessage)Message);
                    break;
                case wclWiFiDriAsdMessageType.mtAuth:
                    ShowUnknownAsdMessage(Message);
                    break;
                case wclWiFiDriAsdMessageType.mtSelfId:
                    ShowAsdSelfIdMessage((wclWiFiDriAsdSelfIdMessage)Message);
                    break;
                case wclWiFiDriAsdMessageType.mtSystem:
                    ShowAsdSystemMessage((wclWiFiDriAsdSystemMessage)Message);
                    break;
                case wclWiFiDriAsdMessageType.mtOperatorId:
                    ShowAsdOperatorIdMessage((wclWiFiDriAsdOperatorIdMessage)Message);
                    break;
                default:
                    ShowUnknownAsdMessage(Message);
                    break;
            }
        }

        private void UpdateDroneMessages(TreeNode Node, List<wclWiFiDriMessage> Messages)
        {
            foreach (wclWiFiDriMessage Message in Messages)
            {
                if (Message.Vendor == wclWiFiDriVendor.driAsd)
                {
                    wclWiFiDriAsdMessage AsdMessage = (wclWiFiDriAsdMessage)Message;
                    String MessageType = MessageTypeToText(AsdMessage);

                    TreeNode MessageNode = null;
                    if (Node.Nodes.Count > 0)
                    {
                        foreach (TreeNode TempNode in Node.Nodes)
                        {
                            if (TempNode.Text == MessageType)
                            {
                                MessageNode = TempNode;
                                MessageNode.Tag = null;
                                break;
                            }

                        }
                    }

                    if (MessageNode == null)
                        MessageNode = Node.Nodes.Add(MessageType);
                    MessageNode.Tag = AsdMessage;
                    if (MessageNode.IsSelected)
                        UpdateMessageDetails(MessageNode.Parent.Text, AsdMessage);
                }
            }
        }

        private void UpdateMessageDetails(String Ssid, wclWiFiDriMessage Message)
        {
            ClearMessageDetails();

            if (Message.Vendor == wclWiFiDriVendor.driAsd)
                UpdateAsdMessageDetails(Ssid, (wclWiFiDriAsdMessage)Message);
        }

        private void UpdateMessages(String Ssid, List<wclWiFiDriMessage> Messages)
        {
            TreeNode DroneNode = FindDrone(Ssid);
            if (DroneNode != null)
            {
                UpdateDroneMessages(DroneNode, Messages);
                DroneNode.ExpandAll();
            }
        }

        private void GetDriInfo()
        {
            wclWiFiBss[] BssList;
            Int32 Res = WiFiClient.EnumBss(FId, "", wclWiFiBssType.bssAny, true, out BssList);
            if (Res != wclErrors.WCL_E_SUCCESS)
                Trace("Enum BSS failed", Res);
            else
            {
                if (BssList != null && BssList.Length > 0)
                {
                    List<wclWiFiDriMessage> Messages = new List<wclWiFiDriMessage>();
                    foreach (wclWiFiBss Bss in BssList)
                    {
                        if (Bss.IeRaw != null && Bss.IeRaw.Length > 0)
                        {
                            FParser.ParseDriMessages(Bss, Messages);
                            if (Messages.Count > 0)
                                UpdateMessages(Bss.Ssid, Messages);
                        }
                    }
                }
            }
        }

        private void RestartScan()
        {
            if (FScanActive)
            {
                Int32 Res = WiFiClient.Scan(FId);
                if (Res != wclErrors.WCL_E_SUCCESS)
                {
                    Trace("Restart scan failed", Res);

                    StopScan();
                }
            }
        }

        private void StartScan()
        {
            if (!FScanActive)
            {
                if (FId != Guid.Empty)
                {
                    Int32 Res = WiFiClient.Scan(FId);
                    if (Res != wclErrors.WCL_E_SUCCESS)
                        Trace("Start scan failed", Res);
                    else
                    {
                        btStart.Enabled = false;
                        btStop.Enabled = true;

                        FScanActive = true;
                        FRootNode = tvDrones.Nodes.Add("Drones");

                        Trace("Scan started");
                    }
                }
            }
        }

        private void StopScan()
        {
            if (FScanActive)
            {
                btStart.Enabled = true;
                btStop.Enabled = false;

                FScanActive = false;

                tvDrones.Nodes.Clear();
                FRootNode = null;

                ClearMessageDetails();

                Trace("Scan sopped");
            }
        }

        public fmMain()
        {
            InitializeComponent();
        }

        private void tvDronesAfterSelect(Object sender, TreeViewEventArgs e)
        {
            ClearMessageDetails();

            if (tvDrones.SelectedNode != null)
            {
                if (tvDrones.SelectedNode.Tag != null)
                {
                    UpdateMessageDetails(tvDrones.SelectedNode.Parent.Text,
                        (wclWiFiDriMessage)tvDrones.SelectedNode.Tag);
                }
            }
        }

        private void fmMain_Load(Object sender, EventArgs e)
        {
            WiFiClient = new wclWiFiClient();
            WiFiClient.AfterOpen += WiFiClientAfterOpen;
            WiFiClient.BeforeClose += WiFiClientBeforeClose;

            WiFiEvents = new wclWiFiEvents();
            WiFiEvents.OnAcmInterfaceArrival += WiFiEventsAcmInterfaceArrival;
            WiFiEvents.OnAcmInterfaceRemoval += WiFiEventsAcmInterfaceRemoval;
            WiFiEvents.OnAcmScanComplete += WiFiEventsAcmScanComplete;
            WiFiEvents.OnAcmScanFail += WiFiEventsAcmScanFail;
            WiFiEvents.AfterOpen += WiFiEventsAfterOpen;
            WiFiEvents.BeforeClose += WiFiEventsBeforeClose;
            WiFiEvents.OnMsmRadioStateChange += WiFiEventsMsmRadioStateChange;

            FParser = new wclWiFiDriParser();
            FScanActive = false;
            FRootNode = null;

            Int32 Res = WiFiClient.Open();
            if (Res != wclErrors.WCL_E_SUCCESS)
                Trace("WiFiClient open failed", Res);
            else
            {
                Res = WiFiEvents.Open();
                if (Res != wclErrors.WCL_E_SUCCESS)
                    Trace("WiFiEvents open failed", Res);
                else
                    EnumInterfaces();

                if (Res != wclErrors.WCL_E_SUCCESS)
                    WiFiClient.Close();
            }
        }

        private void WiFiEventsMsmRadioStateChange(Object Sender, Guid IfaceId, wclWiFiPhyRadioState State)
        {
            if (FId == Guid.Empty)
                EnumInterfaces();
            else
            {
                if (FId == IfaceId)
                {
                    if (State.SoftwareState == wclWiFiRadioState.rsOff || State.HardwareState == wclWiFiRadioState.rsOff)
                    {
                        Trace("Adapter disabled");

                        AdapterDisabled();
                    }
                }
            }
        }

        private void WiFiEventsBeforeClose(object sender, EventArgs e)
        {
            Trace("WiFi Events closed");
        }

        private void WiFiEventsAfterOpen(Object sender, EventArgs e)
        {
            Trace("WiFi Events opened");
        }

        private void WiFiEventsAcmScanFail(Object Sender, Guid IfaceId, int Reason)
        {
            if (FScanActive && FId == IfaceId)
            {
                Trace("Scan failed", Reason);

                RestartScan();
            }
        }

        private void WiFiEventsAcmScanComplete(Object Sender, Guid IfaceId)
        {
            if (FScanActive && FId == IfaceId)
            {
                GetDriInfo();

                RestartScan();
            }
        }

        private void WiFiEventsAcmInterfaceRemoval(Object Sender, Guid IfaceId)
        {
            if (FId == IfaceId)
            {
                Trace("Adapter removed");

                AdapterDisabled();
            }
        }

        private void WiFiEventsAcmInterfaceArrival(Object Sender, Guid IfaceId)
        {
            if (FId == Guid.Empty)
                EnumInterfaces();
        }

        private void WiFiClientBeforeClose(Object sender, EventArgs e)
        {
            Trace("WiFi Client closed");
        }

        private void WiFiClientAfterOpen(Object sender, EventArgs e)
        {
            Trace("WiFi Client opened");
        }

        private void btClearClick(Object sender, EventArgs e)
        {
            lbLog.Items.Clear();
        }

        private void btStartClick(Object sender, EventArgs e)
        {
            StartScan();
        }

        private void btStopClick(Object sender, EventArgs e)
        {
            StopScan();
        }

        private void fmMainFormClosed(Object sender, FormClosedEventArgs e)
        {
            StopScan();

            WiFiEvents.Close();
            WiFiClient.Close();
        }
    }
}
