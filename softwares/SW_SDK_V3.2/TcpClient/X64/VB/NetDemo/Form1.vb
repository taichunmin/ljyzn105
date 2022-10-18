Friend Class Form1
    '/******** Func: Open Device  *******************************/
    '//  Param: pucIPAddress: IP Address  example: "192.168.1.250"
    '//         iPort: IP Port example: 60000
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_OpenDevice Lib "SWNetApi.dll" (ByVal pucIPAddress As String, ByVal iPort As Integer) As Byte
    '/******** Func: Close Device *******************************/
    '//  Param: None
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_CloseDevice Lib "SWNetApi.dll" () As Byte
    '/******** Func: GetDeviceInfo. 9Bytes**********/
    '//  Param: bDevAdr: 0xFF
    '//         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_GetDeviceSystemInfo Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal pucSystemInfo() As Byte) As Byte
    '/******** Func: Get Device One Param**********/
    '//  Param: bDevAdr: 0xFF
    '//         pucDevParamAddr: Param Addr			
    '//         pValue: Return Param Value 
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ReadDeviceOneParam Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal pucDevParamAddr As Byte, ByRef pValue As Byte) As Byte
    '/******** Func: Set Device One Param**********/
    '//  Param: bDevAdr: 0xFF
    '//         pucDevParamAddr: Param Addr		
    '//         bValue: Param	
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_SetDeviceOneParam Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal pucDevParamAddr As Byte, ByVal pValue As Byte) As Byte
    '/******** Func: Stop all RF reading**********/
    '//  Param: bDevAdr: 0xFF
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_StopRead Lib "SWNetApi.dll" (ByVal bDevAdr As Byte) As Byte
    '/******** Func: Start all RF reading**********/
    '//  Param: bDevAdr: 0xFF
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_StartRead Lib "SWNetApi.dll" (ByVal bDevAdr As Byte) As Byte
    '/******** Func: Inventory EPC**********/
    '//  Param: bDevAdr: 0xFF
    '//         pBuffer: Get Buffer
    '//         Totallen: Get Buffer Length
    '//         CardNum: Tag Number
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_InventoryG2 Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal pBuffer() As Byte, ByRef Totallen As Short, ByRef CardNum As Short) As Byte
    '/******** Func: Write EPC**********/
    '//  Param: bDevAdr: 0xFF
    '//         Password: Password (4 bytes)
    '//         WriteEPC: Write Data
    '//         WriteEPClen: Write Length
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_WriteEPCG2 Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByRef Password As Byte, ByRef WriteEPC As Short, ByVal WriteEPClen As Byte) As Byte
    '/******** Func: Read Card**********/
    '//  Param: bDevAdr: 0xFF
    '//         Password: Password (4 bytes)
    '//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
    '//         WordPtr:  Start Address 
    '//         ReadEPClen: Read Length
    '//         Data: Read Data
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ReadCardG2 Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal Password() As Byte, ByVal Mem As Byte, ByVal WordPtr As Byte, ByVal ReadEPClen As Byte, ByVal Data() As Byte) As Byte
    '/******** Func: Write Card**********/
    '//  Param: bDevAdr: 0xFF
    '//         Password: Password (4 bytes)
    '//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
    '//         WordPtr:  Start Address 
    '//         WriteEPC: Write Data
    '//         WriteEPClen: Write Length
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_WriteCardG2 Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal Password() As Byte, ByVal Mem As Byte, ByVal WordPtr As Byte, ByVal Writelen As Byte, ByVal Writedata() As Byte) As Byte
    '/******** Func: RelayOn**********/
    '//  Param: bDevAdr: 0xFF
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_RelayOn Lib "SWNetApi.dll" (ByVal bDevAdr As Byte) As Byte
    '/******** Func: RelayOff**********/
    '//  Param: bDevAdr: 0xFF
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_RelayOff Lib "SWNetApi.dll" (ByVal bDevAdr As Byte) As Byte
    '/******** Func: ClearTagBuf(ActiveMode)**********/
    '//  Param: None
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_ClearTagBuf Lib "SWNetApi.dll" () As Byte
    '/******** Func: GetTagBuf(ActiveMode)**********/
    '//  Param: 
    '//         pBuf: Get Buffer
    '//         pLength: Get Buffer Length
    '//         pTagNumber: Tag Number
    '//  Return: Success return 1, failed return 0
    '/*********************************************************/
    Public Declare Function SWNet_GetTagBuf Lib "SWNetApi.dll" (ByVal pBuf() As Byte, ByRef pLength As Integer, ByRef pTagNumber As Integer) As Byte
    '/******** Func: SetFreq**********/
    '//  Param: bDevAdr: 0xFF
    '//         pFreq: Set 2bytes Freq Value
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
    Public Declare Function SWNet_SetFreq Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal pFreq() As Byte) As Byte
    '/******** Func: ReadFreq**********/
    '//  Param: bDevAdr: 0xFF
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
    Public Declare Function SWNet_ReadFreq Lib "SWNetApi.dll" (ByVal bDevAdr As Byte, ByVal pFreq() As Byte) As Byte

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim ret As Byte
        Dim bDevAdr As Byte
        Dim pucSystemInfo(16) As Byte
        ret = SWNet_OpenDevice(TextBox1.Text, 60000)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "OpenSuccess" & vbCrLf
            Button1.Enabled = False
            Button2.Enabled = True
            bDevAdr = 255
            SWNet_GetDeviceSystemInfo(bDevAdr, pucSystemInfo)
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim ret As Byte
        Timer1.Enabled = False
        Button8.Enabled = True
        Button9.Enabled = False
        ret = SWNet_CloseDevice()
        RichTextBox1.Text = RichTextBox1.Text + "Close" & vbCrLf
        Button1.Enabled = True
        Button2.Enabled = False
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Dim ret As Byte
        ret = SWNet_RelayOn(255)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim ret As Byte
        Dim bDevAdr As Byte
        Dim pValue(2) As Byte
        bDevAdr = 255

        '01: Transport
        '02: WorkMode
        '03: DeviceAddr
        '04：FilterTime
        '05: RFPower
        '06: BeepEnable
        '07: UartBaudRate

        ret = SWNet_ReadDeviceOneParam(bDevAdr, 5, pValue(0))
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
            ComboBox2.SelectedIndex = pValue(0)
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Dim ret As Byte
        Dim bDevAdr As Byte
        Dim bValue As Byte
        bDevAdr = 255

        '01: Transport
        '02: WorkMode
        '03: DeviceAddr
        '04：FilterTime
        '05: RFPower
        '06: BeepEnable
        '07: UartBaudRate
        bValue = ComboBox2.SelectedIndex
        ret = SWNet_SetDeviceOneParam(bDevAdr, 5, bValue)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf
        End If
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Dim ret As Byte
        ret = SWNet_RelayOff(255)
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
        ret = SWNet_WriteCardG2(255, Password, 1, 2, 6, arrBuffer)
        If ret = 1 Then
            RichTextBox1.Text = RichTextBox1.Text + "Success" & vbCrLf 
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed" & vbCrLf 
        End If
    End Sub

    Private Sub Button10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button10.Click
        Dim ret As Byte
        Dim arrBuffer(40960) As Byte
        Dim iTagNumber As Short
        Dim iTotalLen As Short
        ret = SWNet_InventoryG2(255, arrBuffer, iTotalLen, iTagNumber)
        If ret = 1 Then
            If iTagNumber <> 0 Then
                Dim bPackLength As Short
                Dim i As Short
                Dim iIndex As Short
                Dim iLength As Short
                Dim str2 As String
                Dim str1 As String
                Dim str3 As String
                Dim bIDLen As Short
                iIndex = 0
                iLength = 0
                str2 = ""
                For iIndex = 0 To iTagNumber - 1
                    bPackLength = arrBuffer(iLength)
                    str2 = ""
                    str1 = ""
                    str1 = Hex(arrBuffer(1 + iLength + 0))
                    If (arrBuffer(1 + iLength + 0) And 128) = 128 Then
                        bIDLen = bPackLength - 7  ' with TimeStamp , last 6 bytes is time
                    Else
                        bIDLen = bPackLength - 1
                    End If
                    str2 = str2 + "Type:" + str1 + " " 'Tag Type
                    str1 = Hex(arrBuffer(1 + iLength + 1))
                    str2 = str2 + "Ant:" + str1 + " Tag:" 'Ant
                    str3 = ""
                    For i = 2 To bIDLen - 1 'TagID
                        str1 = Hex(arrBuffer(1 + iLength + i))
                        str3 = str3 + str1 + " "
                    Next i
                    str2 = str2 + str3
                    str1 = Hex(arrBuffer(1 + iLength + i))
                    str2 = str2 + "RSSI:" + str1 & vbCrLf  'RSSI
                    iLength = iLength + bPackLength + 1
                Next iIndex
                If RichTextBox1.Text.Length > 1000 Then
                    RichTextBox1.Text = ""
                End If
                RichTextBox1.Text = RichTextBox1.Text + str2
            End If
            RichTextBox1.Text = RichTextBox1.Text + "Success"
        Else
            RichTextBox1.Text = RichTextBox1.Text + "Failed"
        End If
    End Sub
    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click
        Timer1.Enabled = False
        Button8.Enabled = True
        Button9.Enabled = False
    End Sub
    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        SWNet_ClearTagBuf()
        Timer1.Interval = 100
        Timer1.Enabled = True
        Button8.Enabled = False
        Button9.Enabled = True
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim ret As Byte
        Dim arrBuffer(1024 * 64) As Byte
        Dim iTagNumber As Integer
        Dim iTotalLen As Integer
        ret = SWNet_GetTagBuf(arrBuffer, iTotalLen, iTagNumber)
        'ret = 2 DataComing  ret = 1 DevOut
        If ret = 2 Then
            If iTagNumber <> 0 Then
                Dim bPackLength As Short
                Dim i As Short
                Dim iIndex As Short
                Dim iLength As Short
                Dim str2 As String
                Dim str1 As String
                Dim str3 As String
                iIndex = 0
                Dim bIDLen As Byte
                iLength = 0
                str2 = ""
                For iIndex = 0 To iTagNumber - 1
                    bPackLength = arrBuffer(iLength)
                    str2 = ""
                    str1 = ""
                    str1 = Hex(arrBuffer(1 + iLength + 0))
                    If (arrBuffer(1 + iLength + 0) And 128) = 128 Then
                        bIDLen = bPackLength - 7  ' with TimeStamp , last 6 bytes is time
                    Else
                        bIDLen = bPackLength - 1
                    End If
                    str2 = str2 + "Type:" + str1 + " " 'Tag Type
                    str1 = Hex(arrBuffer(1 + iLength + 1))
                    str2 = str2 + "Ant:" + str1 + " Tag:" 'Ant
                    str3 = ""
                    For i = 2 To bIDLen - 1 'TagID
                        str1 = Hex(arrBuffer(1 + iLength + i))
                        str3 = str3 + str1 + " "
                    Next i
                    str2 = str2 + str3
                    str1 = Hex(arrBuffer(1 + iLength + i))
                    str2 = str2 + "RSSI:" + str1 & vbCrLf  'RSSI
                    iLength = iLength + bPackLength + 1
                Next iIndex
                If RichTextBox1.Text.Length > 1000 Then
                    RichTextBox1.Text = ""
                End If
                RichTextBox1.Text = RichTextBox1.Text + str2
            End If
            'RichTextBox1.Text = RichTextBox1.Text + "Success"
        End If
    End Sub
End Class