Friend Class Form1
    Public Declare Function SWNet_GetTotalClientIPAndSocket Lib "SWNetServerApi.dll" (ByRef iCnt As Integer, ByVal IPInfo() As Byte) As Byte
    '/******** Func: Listening  *******************************/
    '//  Param: 
    '//         iPort: IP Port example: 60000
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_Listening Lib "SWNetServerApi.dll" (ByVal iPort As Integer) As Byte
    '/******** Func: Close Device *******************************/
    '//  Param: None
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_CloseDevice Lib "SWNetServerApi.dll" () As Byte
    '/******** Func: GetDeviceInfo. 9Bytes**********/
    '//  Param:  iSocket: Socket
    '//          pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_GetDeviceSystemInfo Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal pucSystemInfo() As Byte) As Byte
    '/******** Func: Get Device One Param**********/
    '//  Param: iSocket: Socket
    '//         pucDevParamAddr: Param Addr			
    '//         pValue: Return Param Value 
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ReadDeviceOneParam Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal pucDevParamAddr As Byte, ByRef pValue As Byte) As Byte
    '/******** Func: Set Device One Param**********/
    '//  Param: iSocket: Socket
    '//         pucDevParamAddr: Param Addr		
    '//         bValue: Param	
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_SetDeviceOneParam Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal pucDevParamAddr As Byte, ByVal pValue As Byte) As Byte
    '/******** Func: Stop all RF reading**********/
    '//  Param: iSocket: Socket
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_StopRead Lib "SWNetServerApi.dll" (ByVal iSocket As Integer) As Byte
    '/******** Func: Start all RF reading**********/
    '//  Param: iSocket: Socket
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_StartRead Lib "SWNetServerApi.dll" (ByVal iSocket As Integer) As Byte
    '/******** Func: Inventory EPC**********/
    '//  Param: iSocket: Socket
    '//         pBuffer: Get Buffer
    '//         Totallen: Get Buffer Length
    '//         CardNum: Tag Number
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_InventoryG2 Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal pBuffer() As Byte, ByRef Totallen As Short, ByRef CardNum As Short) As Byte
    '/******** Func: Write EPC**********/
    '//  Param: iSocket: Socket
    '//         Password: Password (4 bytes)
    '//         WriteEPC: Write Data
    '//         WriteEPClen: Write Length
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_WriteEPCG2 Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByRef Password As Byte, ByRef WriteEPC As Short, ByVal WriteEPClen As Byte) As Byte
    '/******** Func: Read Card**********/
    '//  Param: iSocket: Socket
    '//         Password: Password (4 bytes)
    '//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
    '//         WordPtr:  Start Address 
    '//         ReadEPClen: Read Length
    '//         Data: Read Data
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ReadCardG2 Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal Password() As Byte, ByVal Mem As Byte, ByVal WordPtr As Byte, ByVal ReadEPClen As Byte, ByVal Data() As Byte) As Byte
    '/******** Func: Write Card**********/
    '//  Param: iSocket: Socket
    '//         Password: Password (4 bytes)
    '//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
    '//         WordPtr:  Start Address 
    '//         WriteEPC: Write Data
    '//         WriteEPClen: Write Length
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_WriteCardG2 Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal Password() As Byte, ByVal Mem As Byte, ByVal WordPtr As Byte, ByVal Writelen As Byte, ByVal Writedata() As Byte) As Byte
    '/******** Func: RelayOn**********/
    '//  Param: iSocket: Socket
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_RelayOn Lib "SWNetServerApi.dll" (ByVal iSocket As Integer) As Byte
    '/******** Func: RelayOff**********/
    '//  Param: iSocket: Socket
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_RelayOff Lib "SWNetServerApi.dll" (ByVal iSocket As Integer) As Byte
    '/******** Func: ClearTagBuf(ActiveMode)**********/
    '//  Param: None
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ClearTagBuf Lib "SWNetServerApi.dll" () As Byte
    '/******** Func: GetTagBuf(ActiveMode)**********/
    '//  Param: 
    '//         pBuf: Get Buffer
    '//         pLength: Get Buffer Length
    '//         pTagNumber:  Tag Number
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_GetTagBuf Lib "SWNetServerApi.dll" (ByVal pBuf() As Byte, ByRef pLength As Integer, ByRef pTagNumber As Integer) As Byte
    '/******** Func: SetFreq**********/
    '//  Param: iSocket: Socket
    '//         pFreq:Set 2bytes Freq Value
    '//pFreq[0]   pFreq[1]
    '//0x31        0x80     //US Freq
    '//0x4E        0x00     //Europe
    '//0x2C        0xA3     //China
    '//0x29        0x9D     //Korea
    '//0x2E        0x9F     //Australia
    '//0x4E        0x00     //New Zealand
    '//0x4E        0x00     //India
    '//0x2C        0x81     //Singapore
    '//0x2C        0xA3     //Hongkong
    '//0x31        0xA7     //Taiwan
    '//0x31        0x80     //Canada
    '//0x31        0x80     //Mexico
    '//0x31        0x99     //Brazil
    '//0x1C        0x99     //Israel
    '//0x24        0x9D     //South Africa
    '//0x2C        0xA3     //Thailand
    '//0x28        0xA1     //Malaysia
    '//0x29        0x9D     //Japan
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_SetFreq Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal pFreq() As Byte) As Byte
    '/******** Func: ReadFreq**********/
    '//  Param: iSocket: Socket
    '//         pFreq: Return 2bytes Freq Value
    '//pFreq[0]   pFreq[1]
    '//0x31        0x80     //US Freq
    '//0x4E        0x00     //Europe
    '//0x2C        0xA3     //China
    '//0x29        0x9D     //Korea
    '//0x2E        0x9F     //Australia
    '//0x4E        0x00     //New Zealand
    '//0x4E        0x00     //India
    '//0x2C        0x81     //Singapore
    '//0x2C        0xA3     //Hongkong
    '//0x31        0xA7     //Taiwan
    '//0x31        0x80     //Canada
    '//0x31        0x80     //Mexico
    '//0x31        0x99     //Brazil
    '//0x1C        0x99     //Israel
    '//0x24        0x9D     //South Africa
    '//0x2C        0xA3     //Thailand
    '//0x28        0xA1     //Malaysia
    '//0x29        0x9D     //Japan
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ReadFreq Lib "SWNetServerApi.dll" (ByVal iSocket As Integer, ByVal pFreq() As Byte) As Byte

    Public g_iSockTotal As Integer
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim ret As Byte
        Dim iSocket As Integer
        iSocket = System.Convert.ToInt32(TextBox1.Text)
        ret = SWNet_Listening(iSocket)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "ListeningSuccess" & vbCrLf
            Button1.Enabled = False
            Button2.Enabled = True
            SWNet_ClearTagBuf()
            Timer1.Interval = 50
            Timer1.Enabled = True
            g_iSockTotal = 0
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim ret As Byte
        Timer1.Enabled = False
        ret = SWNet_CloseDevice()
        RichTextBox1.Text = RichTextBox1.Text + "Close" & vbCrLf
        Button1.Enabled = True
        Button2.Enabled = False
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Dim ret As Byte
        Dim iSock As Integer
        iSock = System.Convert.ToInt32(TextBox2.Text)
        ret = SWNet_RelayOn(iSock)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim ret As Byte
        Dim pValue(2) As Byte
        Dim iSock As Integer
        iSock = System.Convert.ToInt32(TextBox2.Text)
        '01: Transport
        '02: WorkMode
        '03: DeviceAddr
        '04：FilterTime
        '05: RFPower
        '06: BeepEnable
        '07: UartBaudRate

        ret = SWNet_ReadDeviceOneParam(iSock, 5, pValue(0))
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
            ComboBox2.SelectedIndex = pValue(0)
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Dim ret As Byte
        Dim iSock As Integer
        Dim bValue As Byte
        iSock = System.Convert.ToInt32(TextBox2.Text)
        '01: Transport
        '02: WorkMode
        '03: DeviceAddr
        '04：FilterTime
        '05: RFPower
        '06: BeepEnable
        '07: UartBaudRate
        bValue = ComboBox2.SelectedIndex
        ret = SWNet_SetDeviceOneParam(iSock, 5, bValue)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Dim ret As Byte
        Dim iSock As Integer
        iSock = System.Convert.ToInt32(TextBox2.Text)
        ret = SWNet_RelayOff(iSock)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        Dim ret As Byte
        Dim Password(4) As Byte
        Dim arrBuffer(12) As Byte
        Dim iSock As Integer
        iSock = System.Convert.ToInt32(TextBox2.Text)
        Password(0) = 0
        Password(1) = 0
        Password(2) = 0
        Password(3) = 0
        arrBuffer(0) = 0
        arrBuffer(1) = 1
        arrBuffer(2) = 2
        arrBuffer(3) = 3
        arrBuffer(4) = 4
        arrBuffer(5) = 5
        arrBuffer(6) = 6
        arrBuffer(7) = 7
        arrBuffer(8) = 8
        arrBuffer(9) = 9
        arrBuffer(10) = 10
        arrBuffer(11) = 11
        ret = SWNet_WriteCardG2(iSock, Password, 1, 2, 6, arrBuffer)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub
    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click
        Dim iSock As Integer
        Dim ret As Byte
        iSock = System.Convert.ToInt32(TextBox2.Text)
        ret = SWNet_StopRead(iSock)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub
    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        Dim iSock As Integer
        Dim ret As Byte
        iSock = System.Convert.ToInt32(TextBox2.Text)
        ret = SWNet_StartRead(iSock)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim IPInfo(4096) As Byte
        Dim IPCnt As Integer
        Dim i As Integer

        SWNet_GetTotalClientIPAndSocket(IPCnt, IPInfo)
        If g_iSockTotal <> IPCnt Then
            If g_iSockTotal < IPCnt Then 'Connect
                Dim strSock As String
                Dim iConnectSock As Integer
                Dim strIP As String
                'IPInfo is IP+Socket (17 bytes for 1 group:  first 15bytes is IP such as "192.168.1.250"
                'then 2 bytes is socket, high byte
                'last ip is new coming connect
                Dim ucIP(16) As Byte
                For i = 0 To 14
                    ucIP(i) = IPInfo(g_iSockTotal * 17 + i)
                Next i
                ucIP(15) = 0
                strIP = System.Text.Encoding.GetEncoding("ascii").GetString(ucIP)
                strIP = strIP.Substring(0, 15)
                iConnectSock = IPInfo(g_iSockTotal * 17 + 15) * 256 + IPInfo(g_iSockTotal * 17 + 16)
                strSock = CStr(iConnectSock)
                RichTextBox1.Text = RichTextBox1.Text + strIP + ":" + strSock + " Connect" & vbCrLf
            Else 'Disconnect ,Need to compare old IPinfo, you can solve by yourself, this is not to show

            End If
            g_iSockTotal = IPCnt
            TextBox3.Text = CStr(g_iSockTotal)
        End If
        If IPCnt = 0 Then
            Return
        End If
        Dim iSock As Integer
        iSock = IPInfo(15) * 256 + IPInfo(16)
        TextBox2.Text = CStr(iSock)

        Dim arrBuffer(1024 * 48) As Byte
        Dim iLineCnt As Integer
        Dim iTotalLen As Integer
        Dim bRet As Byte
        iLineCnt = 0
        iTotalLen = 0
        bRet = SWNet_GetTagBuf(arrBuffer, iTotalLen, iLineCnt)
        If bRet = 0 Then
            Return
        End If
        If iTotalLen = 0 Then
            Return
        End If

        Dim j As Integer
        Dim k As Integer
        Dim iTagLength As Integer
        Dim iTagNumber As Integer
        Dim strTagIP As String
        Dim str1 As String
        Dim strSocket As String
        Dim strSN As String
        Dim iTotalCnt As Integer
        iTagLength = 0
        iTagNumber = 0
        strTagIP = ""
        strSocket = ""
        iTotalCnt = 0
        For k = 0 To iLineCnt - 1 'iLineCnt mean pakage number
            'every pakage group is 2 bytes length + 15 bytes ip+ 2bytes socket+ 7bytes SN + 1 bytes tagcnt + tagcontent
            iTagLength = arrBuffer(0 + iTotalCnt) * 256 + arrBuffer(1 + iTotalCnt)  'GetPakageLength
            'get IP
            Dim IP(16) As Byte
            For i = 0 To 14
                IP(i) = arrBuffer(2 + i)
            Next i
            IP(15) = 0
            strTagIP = System.Text.Encoding.GetEncoding("ascii").GetString(IP)
            strTagIP = strTagIP.Substring(0, 15)
            'Get Socket
            Dim iSocket As Integer
            iSocket = arrBuffer(2 + 15 + iTotalCnt) * 256 + arrBuffer(2 + 16 + iTotalCnt)
            strSocket = CStr(iSocket)
            'Get SN
            strSN = ""
            For i = 0 To 6
                str1 = Hex(arrBuffer(2 + 17 + i + iTotalCnt))
                strSN = strSN + str1
            Next i
            RichTextBox1.Text = RichTextBox1.Text + strTagIP + ":" + strSocket + " " + strSN & vbCrLf
            'Get TagCnt
            iTagNumber = arrBuffer(2 + 17 + 7 + iTotalCnt)
            'Get TagContent
            Dim bPackLength As Byte
            Dim bIDLen As Byte
            Dim iLength As Integer
            iLength = 0
            For i = 0 To iTagNumber - 1

                bPackLength = arrBuffer(2 + 17 + 8 + iLength + iTotalCnt)
                Dim str2 As String
                str1 = ""
                str2 = ""
                str1 = Hex(arrBuffer(2 + 17 + 8 + 1 + iLength + iTotalCnt))
                If (arrBuffer(2 + 17 + 8 + 1 + iLength + iTotalCnt) And 128) = 128 Then
                    bIDLen = bPackLength - 7  ' with TimeStamp , last 6 bytes is time
                Else
                    bIDLen = bPackLength - 1
                End If
                str2 = str2 + "Type:" + str1 + " "  'Tag Type

                str1 = Hex(arrBuffer(2 + 17 + 8 + 2 + iLength + iTotalCnt))
                str2 = str2 + "Ant:" + str1 + " Tag:" 'Ant

                Dim str3 As String
                str3 = ""
                For j = 2 To bIDLen - 1
                    str1 = Hex(arrBuffer(2 + 17 + 8 + 1 + iLength + j + iTotalCnt))
                    str3 = str3 + str1 + " "
                Next j
                str2 = str2 + str3
                str1 = Hex(arrBuffer(2 + 17 + 8 + 1 + iLength + j + iTotalCnt))
                str2 = str2 + "RSSI:" + str1 & vbCrLf    'RSSI
                iLength = iLength + bPackLength + 1
                If RichTextBox1.Text.Length > 1000 Then
                    RichTextBox1.Text = ""
                End If
                RichTextBox1.Text = RichTextBox1.Text + str2
            Next i
            iTotalCnt = iTotalCnt + iTagLength + 2
        Next k
    End Sub
End Class