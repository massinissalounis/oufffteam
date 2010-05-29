VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form FormStep1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "FormStep1"
   ClientHeight    =   24615
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   29910
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   24615
   ScaleWidth      =   29910
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   52
      Left            =   7080
      TabIndex        =   93
      Top             =   19200
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H0080FF80&
         Caption         =   "Terminer"
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
         Index           =   6
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   94
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         Caption         =   "Déplacement terminée !"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00008000&
         Height          =   495
         Index           =   2
         Left            =   120
         TabIndex        =   96
         Top             =   840
         Width           =   6255
      End
      Begin VB.Label LabelMsgOKMove 
         Alignment       =   2  'Center
         Caption         =   "MsgOK"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2175
         Left            =   240
         TabIndex        =   95
         Top             =   1560
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Erreur !!! "
      Height          =   4695
      Index           =   98
      Left            =   24240
      TabIndex        =   89
      Top             =   0
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Terminer"
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
         Index           =   5
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   90
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label LabelTellMeWhyMove 
         Alignment       =   2  'Center
         Caption         =   "TellMeWhy"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2295
         Left            =   240
         TabIndex        =   92
         Top             =   1440
         Width           =   6015
      End
      Begin VB.Label Label21 
         Alignment       =   2  'Center
         Caption         =   "Impossible de déplacer la OufffLib !!!"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   495
         Left            =   120
         TabIndex        =   91
         Top             =   840
         Width           =   6255
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Déplacement "
      Height          =   4695
      Index           =   42
      Left            =   7080
      TabIndex        =   85
      Top             =   14400
      Visible         =   0   'False
      Width           =   6495
      Begin MSComctlLib.ProgressBar ProgressBarCurrentActionMove 
         Height          =   495
         Left            =   240
         TabIndex        =   86
         Top             =   2280
         Width           =   6015
         _ExtentX        =   10610
         _ExtentY        =   873
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label Label20 
         Alignment       =   2  'Center
         Caption         =   "Action en cours :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   88
         Top             =   1320
         Width           =   6015
      End
      Begin VB.Label LabelCurrentActionMove 
         Alignment       =   2  'Center
         Caption         =   "LabelCurrentAction"
         Height          =   255
         Left            =   240
         TabIndex        =   87
         Top             =   1800
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Récapitulatif "
      Height          =   4695
      Index           =   32
      Left            =   7080
      TabIndex        =   79
      Top             =   9600
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton CmdPrev 
         Caption         =   "< Précédent"
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
         Index           =   4
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   82
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdNext 
         BackColor       =   &H00C0FFC0&
         Caption         =   "Continuer >"
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
         Index           =   4
         Left            =   4560
         Style           =   1  'Graphical
         TabIndex        =   81
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdExit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Annuler"
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
         Index           =   4
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   80
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label LabelMovePathRecap 
         Alignment       =   2  'Center
         Caption         =   "MovePath"
         Height          =   495
         Left            =   240
         TabIndex        =   84
         Top             =   2400
         Width           =   6015
      End
      Begin VB.Label Label16 
         Alignment       =   2  'Center
         Caption         =   "La OufffLib va être déplacée dans le répertoire suivant :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   83
         Top             =   1680
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   43
      Left            =   13680
      TabIndex        =   69
      Top             =   14400
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H0080FF80&
         Caption         =   "Terminer"
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
         Index           =   3
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   70
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label LabelRepOk 
         Alignment       =   2  'Center
         Caption         =   "LabelRepOk"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   1095
         Left            =   480
         TabIndex        =   73
         Top             =   2760
         Width           =   5535
      End
      Begin VB.Label Label17 
         Alignment       =   2  'Center
         Caption         =   "La OufffLib a été réparée."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   480
         TabIndex        =   72
         Top             =   2040
         Width           =   5535
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         Caption         =   "Réparation terminée !"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00008000&
         Height          =   495
         Index           =   1
         Left            =   120
         TabIndex        =   71
         Top             =   840
         Width           =   6255
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Erreur !!! "
      Height          =   4695
      Index           =   33
      Left            =   13680
      TabIndex        =   65
      Top             =   9600
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Terminer"
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
         Index           =   2
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   66
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label TellMeWhyErrRep 
         Alignment       =   2  'Center
         Caption         =   "TellMeWhyErrRep"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   1455
         Left            =   240
         TabIndex        =   68
         Top             =   1680
         Width           =   6015
      End
      Begin VB.Label Label14 
         Alignment       =   2  'Center
         Caption         =   "Impossible de réparer la OufffLib !!!"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   495
         Left            =   120
         TabIndex        =   67
         Top             =   840
         Width           =   6255
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   44
      Left            =   20280
      TabIndex        =   57
      Top             =   14400
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H0080FF80&
         Caption         =   "Terminer"
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
         Index           =   1
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   61
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label13 
         Alignment       =   2  'Center
         Caption         =   "ATTENTION : La désinstallation sera complète après avoir redémarrer le PC."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   615
         Left            =   480
         TabIndex        =   60
         Top             =   2760
         Width           =   5535
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         Caption         =   "Suppression réussite !"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00008000&
         Height          =   495
         Index           =   0
         Left            =   120
         TabIndex        =   59
         Top             =   840
         Width           =   6255
      End
      Begin VB.Label Label11 
         Alignment       =   2  'Center
         Caption         =   "La OufffLib a été complètement supprimée."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   480
         TabIndex        =   58
         Top             =   2040
         Width           =   5535
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   34
      Left            =   20280
      TabIndex        =   53
      Top             =   9600
      Visible         =   0   'False
      Width           =   6495
      Begin MSComctlLib.ProgressBar UninstallProgressBar 
         Height          =   495
         Left            =   240
         TabIndex        =   54
         Top             =   2520
         Width           =   6015
         _ExtentX        =   10610
         _ExtentY        =   873
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label Label12 
         Alignment       =   2  'Center
         Caption         =   "Action en cours :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   56
         Top             =   1560
         Width           =   6015
      End
      Begin VB.Label LabelUninstallCurrentAction 
         Alignment       =   2  'Center
         Caption         =   "UninstallCurrentAction"
         Height          =   255
         Left            =   240
         TabIndex        =   55
         Top             =   2040
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   24
      Left            =   20280
      TabIndex        =   47
      Top             =   4800
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton CmdPrev 
         Caption         =   "< Précédent"
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
         Index           =   5
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   50
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdNext 
         BackColor       =   &H00C0FFC0&
         Caption         =   "Continuer >"
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
         Index           =   5
         Left            =   4560
         Style           =   1  'Graphical
         TabIndex        =   49
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdExit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Annuler"
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
         Index           =   5
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   48
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label10 
         Alignment       =   2  'Center
         Caption         =   "Tous les fichiers contenus dans les répertoires de la OufffLib vont être supprimé."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   480
         TabIndex        =   52
         Top             =   2280
         Width           =   5535
      End
      Begin VB.Label Label9 
         Alignment       =   2  'Center
         Caption         =   "Vous êtes sur le point de désinstaller la OufffLib."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   51
         Top             =   1440
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   23
      Left            =   13680
      TabIndex        =   46
      Top             =   4800
      Visible         =   0   'False
      Width           =   6495
      Begin MSComctlLib.ProgressBar ProgressBarRep 
         Height          =   495
         Left            =   600
         TabIndex        =   62
         Top             =   2280
         Width           =   5055
         _ExtentX        =   8916
         _ExtentY        =   873
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label Label15 
         Alignment       =   2  'Center
         Caption         =   "Réparation en cours..."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   120
         TabIndex        =   64
         Top             =   1680
         Width           =   6255
      End
      Begin VB.Label LabelRepEnCours 
         Alignment       =   2  'Center
         Caption         =   "LabelRepEnCours"
         Height          =   255
         Left            =   600
         TabIndex        =   63
         Top             =   2880
         Width           =   5055
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   22
      Left            =   7080
      TabIndex        =   42
      Top             =   4800
      Visible         =   0   'False
      Width           =   6495
      Begin VB.DriveListBox DriveMove 
         Height          =   315
         Left            =   4560
         TabIndex        =   75
         Top             =   240
         Width           =   1695
      End
      Begin VB.DirListBox DirMove 
         Height          =   2115
         Left            =   240
         TabIndex        =   74
         Top             =   720
         Width           =   6015
      End
      Begin VB.CommandButton CmdExit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Annuler"
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
         Index           =   3
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   45
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdNext 
         BackColor       =   &H00C0FFC0&
         Caption         =   "Continuer >"
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
         Index           =   3
         Left            =   4560
         Style           =   1  'Graphical
         TabIndex        =   44
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdPrev 
         Caption         =   "< Précédent"
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
         Index           =   3
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   43
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label19 
         Caption         =   "Choisissez le nouveau répertoire de la OufffLib :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   78
         Top             =   360
         Width           =   5415
      End
      Begin VB.Label Label18 
         Caption         =   "Déplacer la OufffLib vers le répertoire :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   77
         Top             =   3120
         Width           =   6015
      End
      Begin VB.Label MovePath 
         Alignment       =   2  'Center
         Caption         =   "MovePath"
         Height          =   495
         Left            =   240
         TabIndex        =   76
         Top             =   3360
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   51
      Left            =   480
      TabIndex        =   38
      Top             =   19200
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H0080FF80&
         Caption         =   "Terminer"
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
         Index           =   0
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   39
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label MsgOK 
         Alignment       =   2  'Center
         Caption         =   "MsgOK"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2295
         Left            =   240
         TabIndex        =   41
         Top             =   1560
         Width           =   6015
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         Caption         =   "Installation terminée !"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00008000&
         Height          =   495
         Index           =   51
         Left            =   120
         TabIndex        =   40
         Top             =   840
         Width           =   6255
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Erreur !!! "
      Height          =   4695
      Index           =   99
      Left            =   17640
      TabIndex        =   34
      Top             =   0
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton Exit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Terminer"
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
         Index           =   4
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   35
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label8 
         Alignment       =   2  'Center
         Caption         =   "Impossible d'installer la OufffLib !!!"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   495
         Left            =   120
         TabIndex        =   37
         Top             =   840
         Width           =   6255
      End
      Begin VB.Label TellMeWhy 
         Alignment       =   2  'Center
         Caption         =   "TellMeWhy"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2295
         Left            =   240
         TabIndex        =   36
         Top             =   1440
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Installation "
      Height          =   4695
      Index           =   41
      Left            =   480
      TabIndex        =   30
      Top             =   14400
      Visible         =   0   'False
      Width           =   6495
      Begin MSComctlLib.ProgressBar ProgressBarCurrentAction 
         Height          =   495
         Left            =   240
         TabIndex        =   33
         Top             =   2280
         Width           =   6015
         _ExtentX        =   10610
         _ExtentY        =   873
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label LabelCurrentAction 
         Alignment       =   2  'Center
         Caption         =   "LabelCurrentAction"
         Height          =   255
         Left            =   240
         TabIndex        =   32
         Top             =   1800
         Width           =   6015
      End
      Begin VB.Label Label5 
         Alignment       =   2  'Center
         Caption         =   "Action en cours :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   31
         Top             =   1320
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Récapitulatif "
      Height          =   4695
      Index           =   31
      Left            =   480
      TabIndex        =   24
      Top             =   9600
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton CmdExit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Annuler"
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
         Index           =   0
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   27
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdNext 
         BackColor       =   &H00C0FFC0&
         Caption         =   "Continuer >"
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
         Index           =   0
         Left            =   4560
         Style           =   1  'Graphical
         TabIndex        =   26
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdPrev 
         Caption         =   "< Précédent"
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
         Index           =   0
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   25
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label6 
         Alignment       =   2  'Center
         Caption         =   "La OufffLib va être installée dans le répertoire suivant :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   29
         Top             =   1680
         Width           =   6015
      End
      Begin VB.Label RecapInstallPath 
         Alignment       =   2  'Center
         Caption         =   "InstallPath"
         Height          =   495
         Left            =   240
         TabIndex        =   28
         Top             =   2400
         Width           =   6015
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   0
      Left            =   4440
      TabIndex        =   17
      Top             =   0
      Visible         =   0   'False
      Width           =   6495
      Begin MSComctlLib.ProgressBar ProgressBarScan 
         Height          =   495
         Left            =   720
         TabIndex        =   19
         Top             =   1920
         Width           =   5055
         _ExtentX        =   8916
         _ExtentY        =   873
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label LabelActionEnCours 
         Alignment       =   2  'Center
         Caption         =   "ActionEnCours"
         Height          =   255
         Left            =   720
         TabIndex        =   20
         Top             =   2520
         Width           =   5055
      End
      Begin VB.Label Label4 
         Alignment       =   2  'Center
         Caption         =   "Analyse du système en cours..."
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   120
         TabIndex        =   18
         Top             =   1440
         Width           =   6255
      End
   End
   Begin VB.Frame Step 
      Height          =   4695
      Index           =   1
      Left            =   11040
      TabIndex        =   8
      Top             =   0
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton CmdPrev 
         Caption         =   "< Précédent"
         Enabled         =   0   'False
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
         Index           =   1
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   21
         Top             =   3960
         Visible         =   0   'False
         Width           =   1695
      End
      Begin VB.OptionButton SelectTask 
         Caption         =   "Supprimer la OufffLib"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Index           =   3
         Left            =   960
         TabIndex        =   15
         Top             =   2760
         Width           =   3375
      End
      Begin VB.OptionButton SelectTask 
         Caption         =   "Réparer la OufffLib"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Index           =   2
         Left            =   960
         TabIndex        =   14
         Top             =   2280
         Width           =   3375
      End
      Begin VB.OptionButton SelectTask 
         Caption         =   "Déplacer la OufffLib"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Index           =   1
         Left            =   960
         TabIndex        =   13
         Top             =   1800
         Width           =   3375
      End
      Begin VB.OptionButton SelectTask 
         Caption         =   "Installer la OufffLib"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Index           =   0
         Left            =   960
         TabIndex        =   11
         Top             =   1320
         Value           =   -1  'True
         Width           =   3375
      End
      Begin VB.CommandButton CmdExit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Annuler"
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
         Index           =   1
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   10
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdNext 
         BackColor       =   &H00C0FFC0&
         Caption         =   "Continuer >"
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
         Index           =   1
         Left            =   4560
         Style           =   1  'Graphical
         TabIndex        =   9
         Top             =   3960
         Width           =   1695
      End
      Begin VB.Label Label3 
         Alignment       =   2  'Center
         Caption         =   "Selectionner la tâche à effectuer :"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   120
         TabIndex        =   12
         Top             =   720
         Width           =   6255
      End
   End
   Begin VB.Frame Step 
      Caption         =   " Configuration "
      Height          =   4695
      Index           =   21
      Left            =   480
      TabIndex        =   1
      Top             =   4800
      Visible         =   0   'False
      Width           =   6495
      Begin VB.CommandButton CmdPrev 
         Caption         =   "< Précédent"
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
         Index           =   2
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   22
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdNext 
         BackColor       =   &H00C0FFC0&
         Caption         =   "Continuer >"
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
         Index           =   2
         Left            =   4560
         Style           =   1  'Graphical
         TabIndex        =   7
         Top             =   3960
         Width           =   1695
      End
      Begin VB.CommandButton CmdExit 
         BackColor       =   &H00C0C0FF&
         Caption         =   "Annuler"
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
         Index           =   2
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   6
         Top             =   3960
         Width           =   1695
      End
      Begin VB.DirListBox Dir 
         Height          =   2115
         Left            =   240
         TabIndex        =   4
         Top             =   720
         Width           =   6015
      End
      Begin VB.DriveListBox Drive 
         Height          =   315
         Left            =   4320
         TabIndex        =   3
         Top             =   240
         Width           =   1935
      End
      Begin VB.Label InstallPath 
         Alignment       =   2  'Center
         Caption         =   "InstallPath"
         Height          =   495
         Left            =   240
         TabIndex        =   23
         Top             =   3360
         Width           =   6015
      End
      Begin VB.Label Label2 
         Caption         =   "L'installation de la OufffLib va s'effectuer dans le répertoire :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   3120
         Width           =   6015
      End
      Begin VB.Label Label1 
         Caption         =   "Choisissez le répertoire où installer la OufffLib :"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   5415
      End
   End
   Begin VB.PictureBox Picture1 
      Height          =   4335
      Left            =   480
      Picture         =   "FormStep1.frx":0000
      ScaleHeight     =   4275
      ScaleWidth      =   3675
      TabIndex        =   0
      Top             =   120
      Width           =   3735
   End
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
      Left            =   480
      TabIndex        =   16
      Top             =   4560
      Width           =   3735
   End
End
Attribute VB_Name = "FormStep1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public NumStep As Integer
Public CurrentStep As Integer
Public PrevStep As Integer


Private Sub CmdExit_Click(Index As Integer)
    Call FormMain.CmdExit_Click
End Sub

Private Sub CmdNext_Click(Index As Integer)
    NumStep = NumStep + 1
    Call ManageStep
End Sub

Private Sub CmdPrev_Click(Index As Integer)
    NumStep = NumStep - 1
    Call ManageStep
End Sub

Private Sub Dir_Change()
    InstallPath.Caption = Replace(Dir.Path & "\OufffLib\", "\\", "\")
    RecapInstallPath.Caption = Replace(Dir.Path & "\OufffLib\", "\\", "\")
End Sub

Private Sub DirMove_Change()
    MovePath.Caption = Replace(DirMove.Path & "\OufffLib\", "\\", "\")
    LabelMovePathRecap.Caption = Replace(DirMove.Path & "\OufffLib\", "\\", "\")
End Sub

Private Sub Drive_Change()
    On Error GoTo ErrDirPath
    
    Dir.Path = Drive.Drive
    GoTo EndDrive_Change
    
ErrDirPath:
    On Error GoTo 0
    MsgBox ("Impossible de lire le lecteur selectionné !")
    Drive.Drive = "c:"
EndDrive_Change:
 
End Sub

Private Sub DriveMove_Change()
    On Error GoTo ErrDriveMovePath
    
    DirMove.Path = DriveMove.Drive
    GoTo EndDriveMove_Change
    
ErrDriveMovePath:
    On Error GoTo 0
    MsgBox ("Impossible de lire le lecteur selectionné !")
    DriveMove.Drive = "c:"
EndDriveMove_Change:
 
End Sub

Private Sub Exit_Click(Index As Integer)
    End
End Sub

Private Sub Form_Load()
    Me.Caption = FormMain.Caption
    FormMain.Hide
    NumStep = 0
    
    FormStep1.Caption = MAIN_WINDOW_TITLE
    FormStep1.LabelVersion.Caption = "Version : " & MAIN_VERSION & " - " & MAIN_DATE_CREATION
    
    ' Config des tailles des fenetres
    Me.Width = 11460
    Me.Height = 5505
    
    Picture1.Top = 120
    Picture1.Left = 480
    
    ' Activation du premier cadre
    Call SetActiveStep(0)
        
    ' Préchargement de la liste de fichiers
    InstallPath.Caption = Dir.Path & "\OufffLib"
    RecapInstallPath.Caption = Dir.Path & "\OufffLib"
    MovePath.Caption = Replace(DirMove.Path & "\OufffLib\", "\\", "\")
    LabelMovePathRecap.Caption = Replace(DirMove.Path & "\OufffLib\", "\\", "\")
    
    ' Activation de l'étape 1
    PrevStep = 0
    Call ManageStep
End Sub

Public Sub SetActiveStep(Index As Integer)
    PrevStep = CurrentStep
    CurrentStep = Index
    
    Step(CurrentStep).Width = 6495
    Step(CurrentStep).Height = 4695
    Step(CurrentStep).Top = 120
    Step(CurrentStep).Left = 4560

    Step(CurrentStep).Visible = True
    Step(PrevStep).Visible = False
    
End Sub

