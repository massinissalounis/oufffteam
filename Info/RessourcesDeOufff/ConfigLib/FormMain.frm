VERSION 5.00
Begin VB.Form FormMain 
   Caption         =   "Form1"
   ClientHeight    =   5415
   ClientLeft      =   120
   ClientTop       =   420
   ClientWidth     =   10080
   ForeColor       =   &H00008000&
   LinkTopic       =   "Form1"
   ScaleHeight     =   5415
   ScaleWidth      =   10080
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame Frame6 
      Height          =   735
      Left            =   3720
      TabIndex        =   16
      Top             =   3840
      Width           =   6255
      Begin VB.Label LabelNomLIB 
         Alignment       =   2  'Center
         Caption         =   "Création impossible"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000C0&
         Height          =   255
         Left            =   120
         TabIndex        =   18
         Top             =   360
         Width           =   6015
      End
      Begin VB.Label Label3 
         Alignment       =   2  'Center
         Caption         =   "Nom de la Lib à créer :"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   17
         Top             =   120
         Width           =   6015
      End
   End
   Begin VB.Frame Frame5 
      Height          =   735
      Left            =   3720
      TabIndex        =   13
      Top             =   2880
      Width           =   6255
      Begin VB.Label LabelLIB 
         Alignment       =   2  'Center
         Caption         =   "Aucun"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000C0&
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   360
         Width           =   6015
      End
      Begin VB.Label Label6 
         Alignment       =   2  'Center
         Caption         =   "Fichier .lib associé :"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   120
         Width           =   6015
      End
   End
   Begin VB.Frame Frame4 
      Height          =   735
      Left            =   3720
      TabIndex        =   10
      Top             =   1920
      Width           =   6255
      Begin VB.Label LabelDLL 
         Alignment       =   2  'Center
         Caption         =   "Aucun"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000C0&
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   360
         Width           =   6015
      End
      Begin VB.Label Label4 
         Alignment       =   2  'Center
         Caption         =   "Fichier .dll associé :"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   120
         Width           =   6015
      End
   End
   Begin VB.Frame Frame3 
      Height          =   735
      Left            =   3720
      TabIndex        =   7
      Top             =   960
      Width           =   6255
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "Fichier .h associé :"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   120
         Width           =   6015
      End
      Begin VB.Label LabelH 
         Alignment       =   2  'Center
         Caption         =   "Aucun"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000C0&
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   6015
      End
   End
   Begin VB.CommandButton CmdClose 
      Caption         =   "Fermer"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   7080
      TabIndex        =   6
      Top             =   4800
      Width           =   2775
   End
   Begin VB.CommandButton CmdCreate 
      Caption         =   "Mettre la LIB par défaut"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3720
      TabIndex        =   5
      Top             =   4800
      Width           =   2775
   End
   Begin VB.Frame Frame2 
      Caption         =   " Lib trouvée(s) :"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   4335
      Left            =   120
      TabIndex        =   3
      Top             =   960
      Width           =   3375
      Begin VB.ListBox ListFiles 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   3660
         Left            =   240
         TabIndex        =   4
         Top             =   360
         Width           =   2895
      End
   End
   Begin VB.Frame Frame1 
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   9855
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         Caption         =   "Répertoire en cours : "
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   120
         Width           =   9615
      End
      Begin VB.Label NomRepert 
         Alignment       =   2  'Center
         Caption         =   "NomRepert"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   9615
      End
   End
End
Attribute VB_Name = "FormMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private NomRepertoire As String

Private Sub CmdClose_Click()
    End
End Sub

Private Sub Form_Load()
    FormMain.Caption = MAIN_WINDOW_TITLE
    
    ' Récupération du nom du répertoire
    NomRepertoire = CurDir & "\"
    NomRepert.Caption = NomRepertoire

    ' Lecture du répertoire pour obtenir les .dll dans le répertoire
    FileName = Dir(NomRepertoire)
    While FileName <> ""
        Iterator = InStr(1, FileName, ".dll")
        If Iterator > 0 Then
            If InStrRev(FileName, "-", -1) > 0 Then ' On scanne en partant de la fin pour prendre les version des DLL
                ListFiles.AddItem Mid(FileName, 1, Iterator - 1)
            End If
        End If
        FileName = Dir
    Wend
    
    Call ListFiles_Click    ' On charge le premier fichier
End Sub

Private Sub ListFiles_Click()
    Dim NomLib As String
    NomLib = ListFiles.Text
    
    Iterator = InStrRev(NomLib, "-", -1)
    If Iterator > 0 Then ' On scanne en partant de la fin pour prendre le nom de la DLL
        NomFutureLib = Mid(NomLib, 1, Iterator - 1)
    End If
    
    ' On verifie si le fichier .dll existe
    If (FileExists(NomRepert.Caption & ListFiles.Text & ".dll") = True) Then
        LabelDLL.Caption = ListFiles.Text & ".dll"
        LabelDLL.ForeColor = COULEUR_OK
    Else
        LabelDLL.Caption = "Aucun"
        LabelDLL.ForeColor = COULEUR_NON_OK
    End If
    
    ' On verifie si le fichier .lib existe
    If (FileExists(NomRepert.Caption & ListFiles.Text & ".lib") = True) Then
        LabelLIB.Caption = ListFiles.Text & ".lib"
        LabelLIB.ForeColor = COULEUR_OK
    Else
        LabelLIB.Caption = "Aucun"
        LabelLIB.ForeColor = COULEUR_NON_OK
    End If
    
    ' On verifie si le fichier .h existe
    If (FileExists(NomRepert.Caption & "../Include/W32/" & ListFiles.Text & ".h") = True) Then
        LabelH.Caption = ListFiles.Text & ".h"
        LabelH.ForeColor = COULEUR_OK
    Else
        LabelH.Caption = "Aucun"
        LabelH.ForeColor = COULEUR_NON_OK
    End If
    
    If LabelH.ForeColor = COULEUR_OK And LabelLIB.ForeColor = COULEUR_OK And LabelDLL.ForeColor = COULEUR_OK Then
        LabelNomLIB.Caption = NomFutureLib
        LabelNomLIB.ForeColor = COULEUR_OK
    Else
        LabelNomLIB.Caption = "Création impossible !"
        LabelNomLIB.ForeColor = COULEUR_NON_OK
    End If

End Sub

Private Sub CmdCreate_Click()
    If LabelNomLIB.ForeColor = COULEUR_OK Then
        ' Suppression des anciens fichiers
        On Error GoTo NextStep1
        Kill (NomRepert.Caption & LabelNomLIB & ".dll")
        
NextStep1:
        Resume Next
        On Error GoTo NextStep2
        Kill (NomRepert.Caption & LabelNomLIB & ".lib")
        
NextStep2:
        Resume Next
        On Error GoTo NextStep3
        Kill (NomRepert.Caption & "../Include/W32/" & LabelNomLIB & ".h")
        
NextStep3:
        Resume Next
        On Error GoTo ErrCopy
        
        ' Création des nouveaux fichiers
        FileCopy NomRepert.Caption & ListFiles.Text & ".dll", NomRepert.Caption & LabelNomLIB & ".dll"
        FileCopy NomRepert.Caption & ListFiles.Text & ".lib", NomRepert.Caption & LabelNomLIB & ".lib"
        FileCopy NomRepert.Caption & "../Include/W32/" & ListFiles.Text & ".h", NomRepert.Caption & "../Include/W32/" & LabelNomLIB & ".h"
        
        MsgBox "La lib '" & ListFiles.Text & "' est maintenant la lib par défaut du système."
    Else
ErrCopy:
        ' Impossible de créer la lib
        MsgBox "Impossible de mettre la lib '" & ListFiles.Text & "' par défaut." & Chr(13) & "Cause : Des fichiers sont manquants !"
    End If
    
    On Error GoTo 0
End Sub


