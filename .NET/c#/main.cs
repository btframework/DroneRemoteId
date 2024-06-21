using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

using wclCommon;
using wclWiFi;
using wclDri;

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

        private String MessageTypeToText(wclDriAsdMessage Message)
        {
            switch (Message.MessageType)
            {
                case wclDriAsdMessageType.mtBasicId:
                    return "BASIC ID";
                case wclDriAsdMessageType.mtLocation:
                    return "LOCATION";
                case wclDriAsdMessageType.mtAuth:
                    return "AUTH";
                case wclDriAsdMessageType.mtSelfId:
                    return "SELF ID";
                case wclDriAsdMessageType.mtSystem:
                    return "SYSTEM";
                case wclDriAsdMessageType.mtOperatorId:
                    return "OPERATOR ID";
                default:
                    return "UNKNOWN";
            }
        }

        private String AsdVerticalAccuracyToText(wclDriAsdUavVerticalAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclDriAsdUavVerticalAccuracy.vaUnknown:
                    return "Unknow";
                case wclDriAsdUavVerticalAccuracy.va150M:
                    return "150 m";
                case wclDriAsdUavVerticalAccuracy.va45M:
                    return "45 m";
                case wclDriAsdUavVerticalAccuracy.va25M:
                    return "25 m";
                case wclDriAsdUavVerticalAccuracy.va10M:
                    return "10 m";
                case wclDriAsdUavVerticalAccuracy.va3M:
                    return "3 m";
                case wclDriAsdUavVerticalAccuracy.va1M:
                    return "1 m";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdHeightReferenceToText(wclDriAsdUavHeightReference Reference)
        {
            switch (Reference)
            {
                case wclDriAsdUavHeightReference.hrTakeOff:
                    return "Take off";
                case wclDriAsdUavHeightReference.hrGround:
                    return "Ground";
                default:
                    return "Raw value: 0x" + ((Byte)Reference).ToString("X2");
            }
        }

        private String AsdHorizontalAccuracyToText(wclDriAsdUavHorizontalAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclDriAsdUavHorizontalAccuracy.haUnknown:
                    return "Unknown";
                case wclDriAsdUavHorizontalAccuracy.ha10Nm:
                    return "10 miles";
                case wclDriAsdUavHorizontalAccuracy.ha4Nm:
                    return "4 miles";
                case wclDriAsdUavHorizontalAccuracy.ha2Nm:
                    return "2 miles";
                case wclDriAsdUavHorizontalAccuracy.ha1Nm:
                    return "1 mile";
                case wclDriAsdUavHorizontalAccuracy.ha05Nm:
                    return "0.5 mile";
                case wclDriAsdUavHorizontalAccuracy.ha03Nm:
                    return "0.3 mile";
                case wclDriAsdUavHorizontalAccuracy.ha01Nm:
                    return "0.1 mile";
                case wclDriAsdUavHorizontalAccuracy.ha005Nm:
                    return "0.05 mile";
                case wclDriAsdUavHorizontalAccuracy.ha30M:
                    return "30 meters";
                case wclDriAsdUavHorizontalAccuracy.ha10M:
                    return "10 meters";
                case wclDriAsdUavHorizontalAccuracy.ha3M:
                    return "3 meters";
                case wclDriAsdUavHorizontalAccuracy.ha1M:
                    return "1 meter";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdSpeedAccuracyToText(wclDriAsdUavSpeedAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclDriAsdUavSpeedAccuracy.saUnknown:
                    return "Unknown";
                case wclDriAsdUavSpeedAccuracy.sa10MS:
                    return "10 m/s";
                case wclDriAsdUavSpeedAccuracy.sa3MS:
                    return "3 m/s";
                case wclDriAsdUavSpeedAccuracy.sa1Ms:
                    return "1 m/s";
                case wclDriAsdUavSpeedAccuracy.sa03Ms:
                    return "0.3 m/s";
                default:
                    return "Raw value: 0x" + ((Byte)Accuracy).ToString("X2");
            }
        }

        private String AsdStatusToText(wclDriAsdUavStatus Status)
        {
            switch (Status)
            {
                case wclDriAsdUavStatus.usUndeclared:
                    return "Undeclared";
                case wclDriAsdUavStatus.usGround:
                    return "Ground";
                case wclDriAsdUavStatus.usAirborne:
                    return "Airborne";
                case wclDriAsdUavStatus.usEmergency:
                    return "Emergency";
                case wclDriAsdUavStatus.usFailure:
                    return "Failure";
                default:
                    return "Raw value: 0x" + ((Byte)Status).ToString("X2");
            }
        }

        private String AsdTimestampAccuracyToText(wclDriAsdUavTimestampAccuracy Accuracy)
        {
            switch (Accuracy)
            {
                case wclDriAsdUavTimestampAccuracy.taUnknown:
                    return "Unknown";
                case wclDriAsdUavTimestampAccuracy.ta01s:
                    return "0.1 second";
                case wclDriAsdUavTimestampAccuracy.ta02s:
                    return "0.2 second";
                case wclDriAsdUavTimestampAccuracy.ta03s:
                    return "0.3 second";
                case wclDriAsdUavTimestampAccuracy.ta04s:
                    return "0.4 second";
                case wclDriAsdUavTimestampAccuracy.ta05s:
                    return "0.5 second";
                case wclDriAsdUavTimestampAccuracy.ta06s:
                    return "0.6 second";
                case wclDriAsdUavTimestampAccuracy.ta07s:
                    return "0.7 second";
                case wclDriAsdUavTimestampAccuracy.ta08s:
                    return "0.8 second";
                case wclDriAsdUavTimestampAccuracy.ta09s:
                    return "0.9 second";
                case wclDriAsdUavTimestampAccuracy.ta1s:
                    return "1 second";
                case wclDriAsdUavTimestampAccuracy.ta11s:
                    return "1.1 second";
                case wclDriAsdUavTimestampAccuracy.ta12s:
                    return "1.2 second";
                case wclDriAsdUavTimestampAccuracy.ta13s:
                    return "1.3 second";
                case wclDriAsdUavTimestampAccuracy.ta14s:
                    return "1.4 second";
                case wclDriAsdUavTimestampAccuracy.ta15s:
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

        private String AsdDescriptionTypeToText(wclDriAsdDescriptionType DescriptionType)
        {
            switch (DescriptionType)
            {
                case wclDriAsdDescriptionType.dtText:
                    return "Text";
                case wclDriAsdDescriptionType.dtEmergency:
                    return "Emergency";
                case wclDriAsdDescriptionType.dtExtended:
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

        private String AsdOperatorClassificationToText(wclDriAsdOperatorClassification Classification)
        {
            switch (Classification)
            {
                case wclDriAsdOperatorClassification.ocUndeclared:
                    return "Undeclared";
                case wclDriAsdOperatorClassification.ocEu:
                    return "EU";
                default:
                    return "Raw value: 0x" + ((Byte)Classification).ToString("X2");
            }
        }

        private String AsdLocationTypeToText(wclDriAsdOperatorLocationType Location)
        {
            switch (Location)
            {
                case wclDriAsdOperatorLocationType.ltTakeOff:
                    return "Take off";
                case wclDriAsdOperatorLocationType.ltLiveGnss:
                    return "Live GNSS";
                case wclDriAsdOperatorLocationType.ltFixed:
                    return "Fixed";
                default:
                    return "Raw value: 0x" + ((Byte)Location).ToString("X2");
            }
        }

        private String AsdEuUavCategoryToText(wclDriAsdUavEuCategory Category)
        {
            switch (Category)
            {
                case wclDriAsdUavEuCategory.ucUndeclared:
                    return "Undeclared";
                case wclDriAsdUavEuCategory.ucOpen:
                    return "Open";
                case wclDriAsdUavEuCategory.ucSpecific:
                    return "Specific";
                case wclDriAsdUavEuCategory.ucCertified:
                    return "Certified";
                default:
                    return "Raw value: 0x" + ((Byte)Category).ToString("X2");
            }
        }

        private String AsdEuUavClassToText(wclDriAsdUavEuClass UavClass)
        {
            switch (UavClass)
            {
                case wclDriAsdUavEuClass.ucUnspecified:
                    return "Unspecified";
                case wclDriAsdUavEuClass.ucClass0:
                    return "Class 0";
                case wclDriAsdUavEuClass.ucClass1:
                    return "Class 1";
                case wclDriAsdUavEuClass.ucClass2:
                    return "Class 2";
                case wclDriAsdUavEuClass.ucClass3:
                    return "Class 3";
                case wclDriAsdUavEuClass.ucClass4:
                    return "Class 4";
                case wclDriAsdUavEuClass.ucClass5:
                    return "Class 5";
                case wclDriAsdUavEuClass.ucClass6:
                    return "Class 6";
                default:
                    return "Raw value: 0x" + ((Byte)UavClass).ToString("X2");
            }
        }

        private String AsdIdTypeToText(wclDriAsdIdType IdType)
        {
            switch (IdType)
            {
                case wclDriAsdIdType.itNone:
                    return "None";
                case wclDriAsdIdType.itSerialNumber:
                    return "Serial number";
                case wclDriAsdIdType.itCaaRegistrationId:
                    return "CAA registration ID";
                case wclDriAsdIdType.itUtmAssignedUuid:
                    return "UTM assigned UUID";
                case wclDriAsdIdType.itSpecificSessionId:
                    return "Specific session ID";
                default:
                    return "Raw value: 0x" + ((Byte)IdType).ToString("X2");
            }
        }

        private String AsdUavTypeToText(wclDriAsdUavType UavType)
        {
            switch (UavType)
            {
                case wclDriAsdUavType.utNone:
                    return "None";
                case wclDriAsdUavType.utAeroplane:
                    return "Aeroplane";
                case wclDriAsdUavType.utCopter:
                    return "Copter";
                case wclDriAsdUavType.utGyroplane:
                    return "Gyroplane";
                case wclDriAsdUavType.utHybridLift:
                    return "Hybrid";
                case wclDriAsdUavType.utOrnithopter:
                    return "Ornithopter";
                case wclDriAsdUavType.utGlider:
                    return "Glider";
                case wclDriAsdUavType.utKite:
                    return "Kite";
                case wclDriAsdUavType.utFreeBalloon:
                    return "Free balloon";
                case wclDriAsdUavType.utCaptiveBalloon:
                    return "Captive balloon";
                case wclDriAsdUavType.utAirship:
                    return "Airship";
                case wclDriAsdUavType.utFreeFallParachute:
                    return "Free fall parachute";
                case wclDriAsdUavType.utRocket:
                    return "Rocket";
                case wclDriAsdUavType.utTetheredPoweredAircraft:
                    return "Tethered powered aircraft";
                case wclDriAsdUavType.utGroundObstacle:
                    return "Ground obstacle";
                default:
                    return "Raw value: 0x" + ((Byte)UavType).ToString("X2");
            }
        }

        private String VendorToText(wclDriMessage Message)
        {
            switch (Message.Vendor)
            {
                case wclDriVendor.driAsd:
                    return "ASD";
                default:
                    return "UKNOWN";
            }
        }
        
        private void ShowAsdLocationMessage(wclDriAsdLocationMessage Message)
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

        private void ShowAsdSelfIdMessage(wclDriAsdSelfIdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("Description");
            Item.SubItems.Add(Message.Description);

            Item = lvDetails.Items.Add("Description Type");
            Item.SubItems.Add(AsdDescriptionTypeToText(Message.DescriptionType));
        }

        private void ShowAsdOperatorIdMessage(wclDriAsdOperatorIdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("ID");
            Item.SubItems.Add(Encoding.ASCII.GetString(Message.Id));

            Item = lvDetails.Items.Add("ID Type");
            Item.SubItems.Add("0x" + Message.IdType.ToString("X2"));
        }

        private void ShowAsdSystemMessage(wclDriAsdSystemMessage Message)
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

        private void ShowAsdBassicIdMessage(wclDriAsdBasicIdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("ID");
            Item.SubItems.Add(Encoding.ASCII.GetString(Message.Id));

            Item = lvDetails.Items.Add("ID type");
            Item.SubItems.Add(AsdIdTypeToText(Message.IdType));

            Item = lvDetails.Items.Add("ID type");
            Item.SubItems.Add(AsdUavTypeToText(Message.UavType));
        }

        private void ShowUnknownAsdMessage(wclDriAsdMessage Message)
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

        private void UpdateAsdMessageDetails(String Ssid, wclDriAsdMessage Message)
        {
            ListViewItem Item = lvDetails.Items.Add("SSID");
            Item.SubItems.Add(Ssid);

            Item = lvDetails.Items.Add("Vendor");
            Item.SubItems.Add(VendorToText(Message));
            
            Item = lvDetails.Items.Add("");
            Item.SubItems.Add("");

            switch (Message.MessageType)
            {
                case wclDriAsdMessageType.mtBasicId:
                    ShowAsdBassicIdMessage((wclDriAsdBasicIdMessage)Message);
                    break;
                case wclDriAsdMessageType.mtLocation:
                    ShowAsdLocationMessage((wclDriAsdLocationMessage)Message);
                    break;
                case wclDriAsdMessageType.mtAuth:
                    ShowUnknownAsdMessage(Message);
                    break;
                case wclDriAsdMessageType.mtSelfId:
                    ShowAsdSelfIdMessage((wclDriAsdSelfIdMessage)Message);
                    break;
                case wclDriAsdMessageType.mtSystem:
                    ShowAsdSystemMessage((wclDriAsdSystemMessage)Message);
                    break;
                case wclDriAsdMessageType.mtOperatorId:
                    ShowAsdOperatorIdMessage((wclDriAsdOperatorIdMessage)Message);
                    break;
                default:
                    ShowUnknownAsdMessage(Message);
                    break;
            }
        }

        private void UpdateDroneMessages(TreeNode Node, List<wclDriMessage> Messages)
        {
            foreach (wclDriMessage Message in Messages)
            {
                if (Message.Vendor == wclDriVendor.driAsd)
                {
                    wclDriAsdMessage AsdMessage = (wclDriAsdMessage)Message;
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

        private void UpdateMessageDetails(String Ssid, wclDriMessage Message)
        {
            ClearMessageDetails();

            if (Message.Vendor == wclDriVendor.driAsd)
                UpdateAsdMessageDetails(Ssid, (wclDriAsdMessage)Message);
        }

        private void UpdateMessages(String Ssid, List<wclDriMessage> Messages)
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
                    List<wclDriMessage> Messages = new List<wclDriMessage>();
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
                        (wclDriMessage)tvDrones.SelectedNode.Tag);
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

        private void WiFiEventsMsmRadioStateChange(Object sender, Guid IfaceId, wclWiFiPhyRadioState State)
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

        private void WiFiEventsBeforeClose(Object sender, EventArgs e)
        {
            Trace("WiFi Events closed");
        }

        private void WiFiEventsAfterOpen(Object sender, EventArgs e)
        {
            Trace("WiFi Events opened");
        }

        private void WiFiEventsAcmScanFail(Object sender, Guid IfaceId, Int32 Reason)
        {
            if (FScanActive && FId == IfaceId)
            {
                Trace("Scan failed", Reason);

                RestartScan();
            }
        }

        private void WiFiEventsAcmScanComplete(Object sender, Guid IfaceId)
        {
            if (FScanActive && FId == IfaceId)
            {
                GetDriInfo();

                RestartScan();
            }
        }

        private void WiFiEventsAcmInterfaceRemoval(Object sender, Guid IfaceId)
        {
            if (FId == IfaceId)
            {
                Trace("Adapter removed");

                AdapterDisabled();
            }
        }

        private void WiFiEventsAcmInterfaceArrival(Object sender, Guid IfaceId)
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
