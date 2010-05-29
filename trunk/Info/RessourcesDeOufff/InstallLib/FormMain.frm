VERSION 5.00
Begin VB.Form FormMain 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   4785
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6045
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   6045
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton CmdExit 
      BackColor       =   &H00C0C0FF&
      Caption         =   "Refuser"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3840
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   4080
      Width           =   1695
   End
   Begin VB.CommandButton CmdNext 
      BackColor       =   &H00C0FFC0&
      Caption         =   "Accepter"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   480
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   4080
      Width           =   1695
   End
   Begin VB.Frame Frame1 
      Caption         =   "Description"
      Height          =   1335
      Left            =   480
      TabIndex        =   1
      Top             =   2640
      Width           =   5055
      Begin VB.Label LabelVersion 
         Alignment       =   2  'Center
         Caption         =   "Version : XXXX - XXXXXXXX"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   960
         Width           =   4815
      End
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         Caption         =   "Ce programme vous permet de créer ou mettre à jour les répertoires et les variables d'environement de la OufffLib."
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Width           =   4815
      End
   End
   Begin VB.PictureBox SmallLogo 
      Height          =   2415
      Left            =   480
      Picture         =   "FormMain.frx":0000
      ScaleHeight     =   2355
      ScaleWidth      =   4995
      TabIndex        =   0
      Top             =   120
      Width           =   5055
   End
End
Attribute VB_Name = "FormMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public Sub CmdExit_Click()
    If (vbYes = MsgBox("Voulez-vous stopper l'installation de la OufffLib ?", vbYesNo, MAIN_WINDOW_TITLE)) Then
        End
    End If
End Sub

Private Sub CmdNext_Click()
    FormStep1.Visible = True
End Sub

Private Sub Form_Load()
    ' Mise à jour des variables
    FormMain.Caption = MAIN_WINDOW_TITLE
    FormMain.LabelVersion.Caption = "Version : " & MAIN_VERSION & " - " & MAIN_DATE_CREATION
End Sub

