Attribute VB_Name = "Déclarations"
Public Declare Function SHFileOperation Lib "shell32.dll" Alias "SHFileOperationA" (lpFileOp As SHFILEOPSTRUCT) As Long

Public Type SHFILEOPSTRUCT
    hWnd As Long
    wFunc As Long
    pFrom As String
    pTo As String
    fFlags As Integer
    fAnyOperationsAborted As Long
    hNameMappings As Long
    lpszProgressTitle As String 'Only used if FOF_SIMPLEPROGRESS
End Type


Public Const FO_COPY = &H2
Public Const FO_DELETE = &H3
Public Const FO_MOVE = &H1
Public Const FO_RENAME = &H4
Public Const FOF_ALLOWUNDO = &H40
Public Const FOF_CONFIRMMOUSE = &H2
Public Const FOF_FILESONLY = &H80
Public Const FOF_MULTIDESTFILES = &H1
Public Const FOF_NOCONFIRMATION = &H10
Public Const FOF_NOCONFIRMMKDIR = &H200
Public Const FOF_RENAMEONCOLLISION = &H8
Public Const FOF_SILENT = &H4
Public Const FOF_SIMPLEPROGRESS = &H100
Public Const FOF_WANTMAPPINGHANDLE = &H20


Function FileExists(FileName As String) As Boolean
    On Error GoTo ErrorFileExists
    ' get the attributes and ensure that it isn't a directory
    FileExists = (GetAttr(FileName) And vbDirectory) = 0
ErrorFileExists:
    ' if an error occurs, this function returns False
End Function

Function DirExists(DirName As String) As Boolean
    On Error GoTo ErrorDirExists
    ' get the attributes and ensure that it isn't a directory
    DirExists = (GetAttr(DirName) And vbDirectory)
ErrorDirExists:
    ' if an error occurs, this function returns False
End Function


