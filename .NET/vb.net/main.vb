Public Class fmMain
    Private WithEvents WiFiClient As wclWiFiClient
    Private WithEvents WiFiEvents As wclWiFiEvents

    Private FId As Guid
    Private FParser As wclWiFiDriParser
    Private FRootNode As TreeNode
    Private FScanActive As Boolean

    Private Sub Trace(Msg As String)
        lbLog.Items.Add(Msg)
        lbLog.TopIndex = lbLog.Items.Count - 1
    End Sub

    Private Sub Trace(Msg As String, Res As Int32)
        Trace(Msg + ": 0x" + Res.ToString("X8"))
    End Sub

    Private Sub AdapterDisabled()
        StopScan()
        FId = Guid.Empty

        btStart.Enabled = False
        btStop.Enabled = False
    End Sub

    Private Sub ClearMessageDetails()
        lvDetails.Items.Clear()
    End Sub

    Private Sub EnumInterfaces()
        btStart.Enabled = False
        btStop.Enabled = False

        Dim Ifaces As wclWiFiInterfaceData() = Nothing
        Dim Res As Int32 = WiFiClient.EnumInterfaces(Ifaces)
        If Res <> wclErrors.WCL_E_SUCCESS Then
            Trace("Enum interfaces failed", Res)
        Else
            If Ifaces Is Nothing OrElse Ifaces.Length = 0 Then
                Trace("No one WiFi interface found")
            Else
                Dim Found As Boolean = False
                For Each Data As wclWiFiInterfaceData In Ifaces
                    Dim Iface As wclWiFiInterface = New wclWiFiInterface(Data.Id)
                    If Iface.Open() = wclErrors.WCL_E_SUCCESS Then
                        Dim States As wclWiFiPhyRadioState() = Nothing
                        Res = Iface.GetRadioState(States)
                        If Res = wclErrors.WCL_E_SUCCESS Then
                            If States IsNot Nothing AndAlso States.Length > 0 Then
                                Dim Enabled As Boolean = False
                                For Each State As wclWiFiPhyRadioState In States
                                    Enabled = State.SoftwareState = wclWiFiRadioState.rsOn AndAlso State.HardwareState = wclWiFiRadioState.rsOn
                                    If Not Enabled Then Exit For
                                Next
                                Found = Enabled
                            End If
                        End If

                        If Found Then FId = Iface.Id
                        Iface.Close()
                    End If

                    If Found Then Exit For
                Next

                If Found Then
                    Trace("Use WiFi interface " + FId.ToString())

                    btStart.Enabled = True
                    btStop.Enabled = False
                End If
            End If
        End If
    End Sub

    Private Function FindDrone(Ssid As String) As TreeNode
        Dim Result As TreeNode = Nothing

        If FRootNode.Nodes.Count > 0 Then
            For Each DroneNode As TreeNode In FRootNode.Nodes
                If DroneNode.Text = Ssid Then
                    Result = DroneNode
                    Exit For
                End If
            Next
        End If

        If Result Is Nothing Then
            Result = FRootNode.Nodes.Add(Ssid)
            FRootNode.ExpandAll()
        End If
        Return Result
    End Function

    Private Function MessageTypeToText(Message As wclDriAsdMessage) As String
        Select Case Message.MessageType
            Case wclDriAsdMessageType.mtBasicId
                Return "BASIC ID"
            Case wclDriAsdMessageType.mtLocation
                Return "LOCATION"
            Case wclDriAsdMessageType.mtAuth
                Return "AUTH"
            Case wclDriAsdMessageType.mtSelfId
                Return "SELF ID"
            Case wclDriAsdMessageType.mtSystem
                Return "SYSTEM"
            Case wclDriAsdMessageType.mtOperatorId
                Return "OPERATOR ID"
            Case Else
                Return "UNKNOWN"
        End Select
    End Function

    Private Function AsdVerticalAccuracyToText(Accuracy As wclDriAsdUavVerticalAccuracy) As String
        Select Case Accuracy
            Case wclDriAsdUavVerticalAccuracy.vaUnknown
                Return "Unknow"
            Case wclDriAsdUavVerticalAccuracy.va150M
                Return "150 m"
            Case wclDriAsdUavVerticalAccuracy.va45M
                Return "45 m"
            Case wclDriAsdUavVerticalAccuracy.va25M
                Return "25 m"
            Case wclDriAsdUavVerticalAccuracy.va10M
                Return "10 m"
            Case wclDriAsdUavVerticalAccuracy.va3M
                Return "3 m"
            Case wclDriAsdUavVerticalAccuracy.va1M
                Return "1 m"
            Case Else
                Return "Raw value: 0x" + CType(Accuracy, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdHeightReferenceToText(Reference As wclDriAsdUavHeightReference) As String
        Select Case Reference
            Case wclDriAsdUavHeightReference.hrTakeOff
                Return "Take off"
            Case wclDriAsdUavHeightReference.hrGround
                Return "Ground"
            Case Else
                Return "Raw value: 0x" + CType(Reference, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdHorizontalAccuracyToText(Accuracy As wclDriAsdUavHorizontalAccuracy) As String
        Select Case Accuracy
            Case wclDriAsdUavHorizontalAccuracy.haUnknown
                Return "Unknown"
            Case wclDriAsdUavHorizontalAccuracy.ha10Nm
                Return "10 miles"
            Case wclDriAsdUavHorizontalAccuracy.ha4Nm
                Return "4 miles"
            Case wclDriAsdUavHorizontalAccuracy.ha2Nm
                Return "2 miles"
            Case wclDriAsdUavHorizontalAccuracy.ha1Nm
                Return "1 mile"
            Case wclDriAsdUavHorizontalAccuracy.ha05Nm
                Return "0.5 mile"
            Case wclDriAsdUavHorizontalAccuracy.ha03Nm
                Return "0.3 mile"
            Case wclDriAsdUavHorizontalAccuracy.ha01Nm
                Return "0.1 mile"
            Case wclDriAsdUavHorizontalAccuracy.ha005Nm
                Return "0.05 mile"
            Case wclDriAsdUavHorizontalAccuracy.ha30M
                Return "30 meters"
            Case wclDriAsdUavHorizontalAccuracy.ha10M
                Return "10 meters"
            Case wclDriAsdUavHorizontalAccuracy.ha3M
                Return "3 meters"
            Case wclDriAsdUavHorizontalAccuracy.ha1M
                Return "1 meter"
            Case Else
                Return "Raw value: 0x" + CType(Accuracy, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdSpeedAccuracyToText(Accuracy As wclDriAsdUavSpeedAccuracy) As String
        Select Case Accuracy
            Case wclDriAsdUavSpeedAccuracy.saUnknown
                Return "Unknown"
            Case wclDriAsdUavSpeedAccuracy.sa10MS
                Return "10 m/s"
            Case wclDriAsdUavSpeedAccuracy.sa3MS
                Return "3 m/s"
            Case wclDriAsdUavSpeedAccuracy.sa1Ms
                Return "1 m/s"
            Case wclDriAsdUavSpeedAccuracy.sa03Ms
                Return "0.3 m/s"
            Case Else
                Return "Raw value: 0x" + CType(Accuracy, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdStatusToText(Status As wclDriAsdUavStatus) As String
        Select Case Status
            Case wclDriAsdUavStatus.usUndeclared
                Return "Undeclared"
            Case wclDriAsdUavStatus.usGround
                Return "Ground"
            Case wclDriAsdUavStatus.usAirborne
                Return "Airborne"
            Case wclDriAsdUavStatus.usEmergency
                Return "Emergency"
            Case wclDriAsdUavStatus.usFailure
                Return "Failure"
            Case Else
                Return "Raw value: 0x" + CType(Status, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdTimestampAccuracyToText(Accuracy As wclDriAsdUavTimestampAccuracy) As String
        Select Case Accuracy
            Case wclDriAsdUavTimestampAccuracy.taUnknown
                Return "Unknown"
            Case wclDriAsdUavTimestampAccuracy.ta01s
                Return "0.1 second"
            Case wclDriAsdUavTimestampAccuracy.ta02s
                Return "0.2 second"
            Case wclDriAsdUavTimestampAccuracy.ta03s
                Return "0.3 second"
            Case wclDriAsdUavTimestampAccuracy.ta04s
                Return "0.4 second"
            Case wclDriAsdUavTimestampAccuracy.ta05s
                Return "0.5 second"
            Case wclDriAsdUavTimestampAccuracy.ta06s
                Return "0.6 second"
            Case wclDriAsdUavTimestampAccuracy.ta07s
                Return "0.7 second"
            Case wclDriAsdUavTimestampAccuracy.ta08s
                Return "0.8 second"
            Case wclDriAsdUavTimestampAccuracy.ta09s
                Return "0.9 second"
            Case wclDriAsdUavTimestampAccuracy.ta1s
                Return "1 second"
            Case wclDriAsdUavTimestampAccuracy.ta11s
                Return "1.1 second"
            Case wclDriAsdUavTimestampAccuracy.ta12s
                Return "1.2 second"
            Case wclDriAsdUavTimestampAccuracy.ta13s
                Return "1.3 second"
            Case wclDriAsdUavTimestampAccuracy.ta14s
                Return "1.4 second"
            Case wclDriAsdUavTimestampAccuracy.ta15s
                Return "1.5 second"
            Case Else
                Return "Raw value: 0x" + CType(Accuracy, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdAltitudeToText(Altitude As Single) As String
        If Altitude = -1000 Then Return "Invalid"
        Return Altitude.ToString()
    End Function

    Private Function AsdDescriptionTypeToText(DescriptionType As wclDriAsdDescriptionType) As String
        Select Case DescriptionType
            Case wclDriAsdDescriptionType.dtText
                Return "Text"
            Case wclDriAsdDescriptionType.dtEmergency
                Return "Emergency"
            Case wclDriAsdDescriptionType.dtExtended
                Return "Extended"
            Case Else
                Return "Raw value: 0x" + CType(DescriptionType, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdDirectionToText(Direction As UInt16) As String
        If Direction > 360 Then Return "Invalid"
        Return Direction.ToString()
    End Function

    Private Function AsdHorizontalSpeedToText(Speed As Single) As String
        If Speed = 255 Then Return "Invalid"
        Return Speed.ToString()
    End Function

    Private Function AsdLatLonToText(LatLon As Double) As String
        If LatLon = 0 Then Return "Invalid"
        Return LatLon.ToString()
    End Function

    Private Function AsdOperatorClassificationToText(Classification As wclDriAsdOperatorClassification) As String
        Select Case Classification
            Case wclDriAsdOperatorClassification.ocUndeclared
                Return "Undeclared"
            Case wclDriAsdOperatorClassification.ocEu
                Return "EU"
            Case Else
                Return "Raw value: 0x" + CType(Classification, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdLocationTypeToText(Location As wclDriAsdOperatorLocationType) As String
        Select Case Location
            Case wclDriAsdOperatorLocationType.ltTakeOff
                Return "Take off"
            Case wclDriAsdOperatorLocationType.ltLiveGnss
                Return "Live GNSS"
            Case wclDriAsdOperatorLocationType.ltFixed
                Return "Fixed"
            Case Else
                Return "Raw value: 0x" + CType(Location, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdEuUavCategoryToText(Category As wclDriAsdUavEuCategory) As String
        Select Case Category
            Case wclDriAsdUavEuCategory.ucUndeclared
                Return "Undeclared"
            Case wclDriAsdUavEuCategory.ucOpen
                Return "Open"
            Case wclDriAsdUavEuCategory.ucSpecific
                Return "Specific"
            Case wclDriAsdUavEuCategory.ucCertified
                Return "Certified"
            Case Else
                Return "Raw value: 0x" + CType(Category, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdEuUavClassToText(UavClass As wclDriAsdUavEuClass) As String
        Select Case UavClass
            Case wclDriAsdUavEuClass.ucUnspecified
                Return "Unspecified"
            Case wclDriAsdUavEuClass.ucClass0
                Return "Class 0"
            Case wclDriAsdUavEuClass.ucClass1
                Return "Class 1"
            Case wclDriAsdUavEuClass.ucClass2
                Return "Class 2"
            Case wclDriAsdUavEuClass.ucClass3
                Return "Class 3"
            Case wclDriAsdUavEuClass.ucClass4
                Return "Class 4"
            Case wclDriAsdUavEuClass.ucClass5
                Return "Class 5"
            Case wclDriAsdUavEuClass.ucClass6
                Return "Class 6"
            Case Else
                Return "Raw value: 0x" + CType(UavClass, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdIdTypeToText(IdType As wclDriAsdIdType) As String
        Select Case IdType
            Case wclDriAsdIdType.itNone
                Return "None"
            Case wclDriAsdIdType.itSerialNumber
                Return "Serial number"
            Case wclDriAsdIdType.itCaaRegistrationId
                Return "CAA registration ID"
            Case wclDriAsdIdType.itUtmAssignedUuid
                Return "UTM assigned UUID"
            Case wclDriAsdIdType.itSpecificSessionId
                Return "Specific session ID"
            Case Else
                Return "Raw value: 0x" + CType(IdType, Byte).ToString("X2")
        End Select
    End Function

    Private Function AsdUavTypeToText(UavType As wclDriAsdUavType) As String
        Select Case UavType
            Case wclDriAsdUavType.utNone
                Return "None"
            Case wclDriAsdUavType.utAeroplane
                Return "Aeroplane"
            Case wclDriAsdUavType.utCopter
                Return "Copter"
            Case wclDriAsdUavType.utGyroplane
                Return "Gyroplane"
            Case wclDriAsdUavType.utHybridLift
                Return "Hybrid"
            Case wclDriAsdUavType.utOrnithopter
                Return "Ornithopter"
            Case wclDriAsdUavType.utGlider
                Return "Glider"
            Case wclDriAsdUavType.utKite
                Return "Kite"
            Case wclDriAsdUavType.utFreeBalloon
                Return "Free balloon"
            Case wclDriAsdUavType.utCaptiveBalloon
                Return "Captive balloon"
            Case wclDriAsdUavType.utAirship
                Return "Airship"
            Case wclDriAsdUavType.utFreeFallParachute
                Return "Free fall parachute"
            Case wclDriAsdUavType.utRocket
                Return "Rocket"
            Case wclDriAsdUavType.utTetheredPoweredAircraft
                Return "Tethered powered aircraft"
            Case wclDriAsdUavType.utGroundObstacle
                Return "Ground obstacle"
            Case Else
                Return "Raw value: 0x" + CType(UavType, Byte).ToString("X2")
        End Select
    End Function

    Private Function VendorToText(Message As wclDriMessage) As String
        Select Case Message.Vendor
            Case wclDriVendor.driAsd
                Return "ASD"
            Case Else
                Return "UKNOWN"
        End Select
    End Function

    Private Sub ShowAsdLocationMessage(Message As wclDriAsdLocationMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("Baro Altitude")
        Item.SubItems.Add(AsdAltitudeToText(Message.BaroAltitude))

        Item = lvDetails.Items.Add("Baro Accuracy")
        Item.SubItems.Add(AsdVerticalAccuracyToText(Message.BaroAccuracy))

        Item = lvDetails.Items.Add("Direction")
        Item.SubItems.Add(AsdDirectionToText(Message.Direction))

        Item = lvDetails.Items.Add("Geo Altitude")
        Item.SubItems.Add(AsdAltitudeToText(Message.GeoAltitude))

        Item = lvDetails.Items.Add("Height")
        Item.SubItems.Add(AsdAltitudeToText(Message.Height))

        Item = lvDetails.Items.Add("Height Reference")
        Item.SubItems.Add(AsdHeightReferenceToText(Message.HeightReference))

        Item = lvDetails.Items.Add("Horizontal Accuracy")
        Item.SubItems.Add(AsdHorizontalAccuracyToText(Message.HorizontalAccuracy))

        Item = lvDetails.Items.Add("Horizontal Speed")
        Item.SubItems.Add(AsdHorizontalSpeedToText(Message.HorizontalSpeed))

        Item = lvDetails.Items.Add("Latitude")
        Item.SubItems.Add(AsdLatLonToText(Message.Latitude))

        Item = lvDetails.Items.Add("Longitude")
        Item.SubItems.Add(AsdLatLonToText(Message.Longitude))

        Item = lvDetails.Items.Add("Speed Accuracy")
        Item.SubItems.Add(AsdSpeedAccuracyToText(Message.SpeedAccuracy))

        Item = lvDetails.Items.Add("Status")
        Item.SubItems.Add(AsdStatusToText(Message.Status))

        Item = lvDetails.Items.Add("Timestamp")
        Item.SubItems.Add(Message.Timestamp.ToString())

        Item = lvDetails.Items.Add("Timestamp Accuracy")
        Item.SubItems.Add(AsdTimestampAccuracyToText(Message.TimestampAccuracy))

        Item = lvDetails.Items.Add("Vertical Accuracy")
        Item.SubItems.Add(AsdVerticalAccuracyToText(Message.VerticalAccuracy))

        Item = lvDetails.Items.Add("Vertical Speed")
        Item.SubItems.Add(Message.VerticalSpeed.ToString())
    End Sub

    Private Sub ShowAsdSelfIdMessage(Message As wclDriAsdSelfIdMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("Description")
        Item.SubItems.Add(Message.Description)

        Item = lvDetails.Items.Add("Description Type")
        Item.SubItems.Add(AsdDescriptionTypeToText(Message.DescriptionType))
    End Sub

    Private Sub ShowAsdOperatorIdMessage(Message As wclDriAsdOperatorIdMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("ID")
        Item.SubItems.Add(Encoding.ASCII.GetString(Message.Id))

        Item = lvDetails.Items.Add("ID Type")
        Item.SubItems.Add("0x" + Message.IdType.ToString("X2"))
    End Sub

    Private Sub ShowAsdSystemMessage(Message As wclDriAsdSystemMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("Area ceiling")
        Item.SubItems.Add(AsdAltitudeToText(Message.AreaCeiling))

        Item = lvDetails.Items.Add("Area count")
        Item.SubItems.Add(Message.AreaCount.ToString())

        Item = lvDetails.Items.Add("Area floor")
        Item.SubItems.Add(AsdAltitudeToText(Message.AreaFloor))

        Item = lvDetails.Items.Add("Area radius")
        Item.SubItems.Add(Message.AreaRadius.ToString())

        Item = lvDetails.Items.Add("Operator altitude")
        Item.SubItems.Add(Message.OperatorAltitude.ToString())

        Item = lvDetails.Items.Add("Operator classification")
        Item.SubItems.Add(AsdOperatorClassificationToText(Message.OperatorClassification))

        Item = lvDetails.Items.Add("Operator latitude")
        Item.SubItems.Add(AsdLatLonToText(Message.OperatorLatitude))

        Item = lvDetails.Items.Add("Operator latitude")
        Item.SubItems.Add(AsdLatLonToText(Message.OperatorLatitude))

        Item = lvDetails.Items.Add("Operator longitude")
        Item.SubItems.Add(AsdLatLonToText(Message.OperatorLongitude))

        Item = lvDetails.Items.Add("Location type")
        Item.SubItems.Add(AsdLocationTypeToText(Message.OperatorLocation))

        Item = lvDetails.Items.Add("Timestamp")
        Item.SubItems.Add(Message.Timestamp.ToString())

        Item = lvDetails.Items.Add("UAV EU category")
        Item.SubItems.Add(AsdEuUavCategoryToText(Message.UavEuCategory))

        Item = lvDetails.Items.Add("UAV EU class")
        Item.SubItems.Add(AsdEuUavClassToText(Message.UavEuClass))
    End Sub

    Private Sub ShowAsdBassicIdMessage(Message As wclDriAsdBasicIdMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("ID")
        Item.SubItems.Add(Encoding.ASCII.GetString(Message.Id))

        Item = lvDetails.Items.Add("ID type")
        Item.SubItems.Add(AsdIdTypeToText(Message.IdType))

        Item = lvDetails.Items.Add("ID type")
        Item.SubItems.Add(AsdUavTypeToText(Message.UavType))
    End Sub

    Private Sub ShowUnknownAsdMessage(Message As wclDriAsdMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("Message type")
        Item.SubItems.Add(CType(Message.MessageType, Byte).ToString("X2"))

        Dim Str As String = ""
        If Message.Data IsNot Nothing AndAlso Message.Data.Length > 0 Then
            For Each b As Byte In Message.Data
                Str = Str + b.ToString("X2")
            Next
        End If
        Item = lvDetails.Items.Add("Raw date")
        Item.SubItems.Add(Str)
    End Sub

    Private Sub UpdateAsdMessageDetails(Ssid As String, Message As wclDriAsdMessage)
        Dim Item As ListViewItem = lvDetails.Items.Add("SSID")
        Item.SubItems.Add(Ssid)

        Item = lvDetails.Items.Add("Vendor")
        Item.SubItems.Add(VendorToText(Message))

        Item = lvDetails.Items.Add("")
        Item.SubItems.Add("")

        Select Case Message.MessageType
            Case wclDriAsdMessageType.mtBasicId
                ShowAsdBassicIdMessage(CType(Message, wclDriAsdBasicIdMessage))
            Case wclDriAsdMessageType.mtLocation
                ShowAsdLocationMessage(CType(Message, wclDriAsdLocationMessage))
            Case wclDriAsdMessageType.mtAuth
                ShowUnknownAsdMessage(Message)
            Case wclDriAsdMessageType.mtSelfId
                ShowAsdSelfIdMessage(CType(Message, wclDriAsdSelfIdMessage))
            Case wclDriAsdMessageType.mtSystem
                ShowAsdSystemMessage(CType(Message, wclDriAsdSystemMessage))
            Case wclDriAsdMessageType.mtOperatorId
                ShowAsdOperatorIdMessage(CType(Message, wclDriAsdOperatorIdMessage))
            Case Else
                ShowUnknownAsdMessage(Message)
        End Select
    End Sub

    Private Sub UpdateDroneMessages(Node As TreeNode, Messages As List(Of wclDriMessage))
        For Each Message As wclDriMessage In Messages
            If Message.Vendor = wclDriVendor.driAsd Then
                Dim AsdMessage As wclDriAsdMessage = CType(Message, wclDriAsdMessage)
                Dim MessageType As String = MessageTypeToText(AsdMessage)

                Dim MessageNode As TreeNode = Nothing
                If Node.Nodes.Count > 0 Then
                    For Each TempNode As TreeNode In Node.Nodes
                        If TempNode.Text = MessageType Then
                            MessageNode = TempNode
                            MessageNode.Tag = Nothing
                            Exit For
                        End If
                    Next
                End If

                If MessageNode Is Nothing Then MessageNode = Node.Nodes.Add(MessageType)
                MessageNode.Tag = AsdMessage
                If MessageNode.IsSelected Then UpdateMessageDetails(MessageNode.Parent.Text, AsdMessage)
            End If
        Next
    End Sub

    Private Sub UpdateMessageDetails(Ssid As String, Message As wclDriMessage)
        ClearMessageDetails()

        If Message.Vendor = wclDriVendor.driAsd Then UpdateAsdMessageDetails(Ssid, CType(Message, wclDriAsdMessage))
    End Sub

    Private Sub UpdateMessages(Ssid As String, Messages As List(Of wclDriMessage))
        Dim DroneNode As TreeNode = FindDrone(Ssid)
        If DroneNode IsNot Nothing Then
            UpdateDroneMessages(DroneNode, Messages)
            DroneNode.ExpandAll()
        End If
    End Sub

    Private Sub GetDriInfo()
        Dim BssList As wclWiFiBss() = Nothing
        Dim Res As Int32 = WiFiClient.EnumBss(FId, "", wclWiFiBssType.bssAny, True, BssList)
        If Res <> wclErrors.WCL_E_SUCCESS Then
            Trace("Enum BSS failed", Res)
        Else
            If BssList IsNot Nothing AndAlso BssList.Length > 0 Then
                Dim Messages As List(Of wclDriMessage) = New List(Of wclDriMessage)()
                For Each Bss As wclWiFiBss In BssList
                    If Bss.IeRaw IsNot Nothing AndAlso Bss.IeRaw.Length > 0 Then
                        FParser.ParseDriMessages(Bss, Messages)
                        If Messages.Count > 0 Then UpdateMessages(Bss.Ssid, Messages)
                    End If
                Next
            End If
        End If
    End Sub

    Private Sub RestartScan()
        If FScanActive Then
            Dim Res As Int32 = WiFiClient.Scan(FId)
            If Res <> wclErrors.WCL_E_SUCCESS Then
                Trace("Restart scan failed", Res)

                StopScan()
            End If
        End If
    End Sub

    Private Sub StartScan()
        If Not FScanActive Then
            If FId <> Guid.Empty Then
                Dim Res As Int32 = WiFiClient.Scan(FId)
                If Res <> wclErrors.WCL_E_SUCCESS Then
                    Trace("Start scan failed", Res)
                Else
                    btStart.Enabled = False
                    btStop.Enabled = True

                    FScanActive = True
                    FRootNode = tvDrones.Nodes.Add("Drones")

                    Trace("Scan started")
                End If
            End If
        End If
    End Sub

    Private Sub StopScan()
        If FScanActive Then
            btStart.Enabled = True
            btStop.Enabled = False

            FScanActive = False

            tvDrones.Nodes.Clear()
            FRootNode = Nothing

            ClearMessageDetails()

            Trace("Scan sopped")
        End If
    End Sub

    Private Sub tvDronesAfterSelect(sender As Object, e As TreeViewEventArgs) Handles tvDrones.AfterSelect
        ClearMessageDetails()

        If tvDrones.SelectedNode IsNot Nothing Then
            If tvDrones.SelectedNode.Tag IsNot Nothing Then
                UpdateMessageDetails(tvDrones.SelectedNode.Parent.Text, CType(tvDrones.SelectedNode.Tag, wclDriMessage))
            End If
        End If
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        WiFiClient = New wclWiFiClient()
        WiFiEvents = New wclWiFiEvents()

        FParser = New wclWiFiDriParser()
        FScanActive = False
        FRootNode = Nothing

        Dim Res As Int32 = WiFiClient.Open()
        If Res <> wclErrors.WCL_E_SUCCESS Then
            Trace("WiFiClient open failed", Res)
        Else
            Res = WiFiEvents.Open()
            If Res <> wclErrors.WCL_E_SUCCESS Then
                Trace("WiFiEvents open failed", Res)
            Else
                EnumInterfaces()
            End If

            If Res <> wclErrors.WCL_E_SUCCESS Then WiFiClient.Close()
        End If
    End Sub

    Private Sub WiFiEventsMsmRadioStateChange(Sender As Object, IfaceId As Guid, State As wclWiFiPhyRadioState) Handles WiFiEvents.OnMsmRadioStateChange
        If FId = Guid.Empty Then
            EnumInterfaces()
        Else
            If FId = IfaceId Then
                If State.SoftwareState = wclWiFiRadioState.rsOff OrElse State.HardwareState = wclWiFiRadioState.rsOff Then
                    Trace("Adapter disabled")

                    AdapterDisabled()
                End If
            End If
        End If
    End Sub

    Private Sub WiFiEventsBeforeClose(sender As Object, e As EventArgs) Handles WiFiEvents.BeforeClose
        Trace("WiFi Events closed")
    End Sub

    Private Sub WiFiEventsAfterOpen(sender As Object, e As EventArgs) Handles WiFiEvents.AfterOpen
        Trace("WiFi Events opened")
    End Sub

    Private Sub WiFiEventsAcmScanFail(Sender As Object, IfaceId As Guid, Reason As Integer) Handles WiFiEvents.OnAcmScanFail
        If FScanActive AndAlso FId = IfaceId Then
            Trace("Scan failed", Reason)

            RestartScan()
        End If
    End Sub

    Private Sub WiFiEventsAcmScanComplete(Sender As Object, IfaceId As Guid) Handles WiFiEvents.OnAcmScanComplete
        If FScanActive AndAlso FId = IfaceId Then
            GetDriInfo()

            RestartScan()
        End If
    End Sub

    Private Sub WiFiEventsAcmInterfaceRemoval(Sender As Object, IfaceId As Guid) Handles WiFiEvents.OnAcmInterfaceRemoval
        If FId = IfaceId Then
            Trace("Adapter removed")

            AdapterDisabled()
        End If
    End Sub

    Private Sub WiFiEventsAcmInterfaceArrival(Sender As Object, IfaceId As Guid) Handles WiFiEvents.OnAcmInterfaceArrival
        If FId = Guid.Empty Then EnumInterfaces()
    End Sub

    Private Sub WiFiClientBeforeClose(sender As Object, e As EventArgs) Handles WiFiClient.BeforeClose
        Trace("WiFi Client closed")
    End Sub

    Private Sub WiFiClientAfterOpen(sender As Object, e As EventArgs) Handles WiFiClient.AfterOpen
        Trace("WiFi Client opened")
    End Sub

    Private Sub btClear_Click(sender As Object, e As EventArgs) Handles btClear.Click
        lbLog.Items.Clear()
    End Sub

    Private Sub btStart_Click(sender As Object, e As EventArgs) Handles btStart.Click
        StartScan()
    End Sub

    Private Sub btStop_Click(sender As Object, e As EventArgs) Handles btStop.Click
        StopScan()
    End Sub

    Private Sub Form1_FormClosed(sender As Object, e As FormClosedEventArgs) Handles MyBase.FormClosed
        StopScan()

        WiFiEvents.Close()
        WiFiClient.Close()
    End Sub
End Class
