<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.textUsername = New System.Windows.Forms.TextBox()
        Me.textPassword = New System.Windows.Forms.TextBox()
        Me.LabelUser = New System.Windows.Forms.Label()
        Me.LabelPass = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.checkPass = New System.Windows.Forms.CheckBox()
        Me.buttonCancel = New System.Windows.Forms.Button()
        Me.buttonLogin = New System.Windows.Forms.Button()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'textUsername
        '
        Me.textUsername.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textUsername.Location = New System.Drawing.Point(224, 96)
        Me.textUsername.Margin = New System.Windows.Forms.Padding(4, 5, 4, 5)
        Me.textUsername.Name = "textUsername"
        Me.textUsername.Size = New System.Drawing.Size(241, 26)
        Me.textUsername.TabIndex = 0
        '
        'textPassword
        '
        Me.textPassword.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textPassword.Location = New System.Drawing.Point(224, 154)
        Me.textPassword.Margin = New System.Windows.Forms.Padding(4, 5, 4, 5)
        Me.textPassword.Name = "textPassword"
        Me.textPassword.PasswordChar = Global.Microsoft.VisualBasic.ChrW(9679)
        Me.textPassword.Size = New System.Drawing.Size(241, 26)
        Me.textPassword.TabIndex = 1
        '
        'LabelUser
        '
        Me.LabelUser.AutoSize = True
        Me.LabelUser.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LabelUser.Location = New System.Drawing.Point(220, 75)
        Me.LabelUser.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.LabelUser.Name = "LabelUser"
        Me.LabelUser.Size = New System.Drawing.Size(87, 20)
        Me.LabelUser.TabIndex = 2
        Me.LabelUser.Text = "Username:"
        '
        'LabelPass
        '
        Me.LabelPass.AutoSize = True
        Me.LabelPass.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LabelPass.Location = New System.Drawing.Point(220, 132)
        Me.LabelPass.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.LabelPass.Name = "LabelPass"
        Me.LabelPass.Size = New System.Drawing.Size(82, 20)
        Me.LabelPass.TabIndex = 3
        Me.LabelPass.Text = "Password:"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 26.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(127, 22)
        Me.Label1.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(260, 39)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Big Gorilla Zoo"
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.checkPass)
        Me.GroupBox1.Controls.Add(Me.buttonCancel)
        Me.GroupBox1.Controls.Add(Me.buttonLogin)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.LabelPass)
        Me.GroupBox1.Controls.Add(Me.LabelUser)
        Me.GroupBox1.Controls.Add(Me.textUsername)
        Me.GroupBox1.Controls.Add(Me.textPassword)
        Me.GroupBox1.Controls.Add(Me.Panel1)
        Me.GroupBox1.Location = New System.Drawing.Point(12, 2)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(498, 261)
        Me.GroupBox1.TabIndex = 5
        Me.GroupBox1.TabStop = False
        '
        'checkPass
        '
        Me.checkPass.AutoSize = True
        Me.checkPass.Location = New System.Drawing.Point(226, 187)
        Me.checkPass.Name = "checkPass"
        Me.checkPass.Size = New System.Drawing.Size(141, 24)
        Me.checkPass.TabIndex = 9
        Me.checkPass.Text = "Show Password"
        Me.checkPass.UseVisualStyleBackColor = True
        '
        'buttonCancel
        '
        Me.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.buttonCancel.Location = New System.Drawing.Point(345, 216)
        Me.buttonCancel.Name = "buttonCancel"
        Me.buttonCancel.Size = New System.Drawing.Size(120, 29)
        Me.buttonCancel.TabIndex = 6
        Me.buttonCancel.Text = "Cancel"
        Me.buttonCancel.UseVisualStyleBackColor = True
        '
        'buttonLogin
        '
        Me.buttonLogin.Location = New System.Drawing.Point(222, 216)
        Me.buttonLogin.Name = "buttonLogin"
        Me.buttonLogin.Size = New System.Drawing.Size(120, 29)
        Me.buttonLogin.TabIndex = 5
        Me.buttonLogin.Text = "Login"
        Me.buttonLogin.UseVisualStyleBackColor = True
        '
        'Panel1
        '
        Me.Panel1.BackgroundImage = Global.EnhancementTwo.My.Resources.Resources.gorilla
        Me.Panel1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.Panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Panel1.Location = New System.Drawing.Point(22, 75)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(170, 170)
        Me.Panel1.TabIndex = 7
        '
        'Form1
        '
        Me.AcceptButton = Me.buttonLogin
        Me.AutoScaleDimensions = New System.Drawing.SizeF(9.0!, 20.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.CancelButton = Me.buttonCancel
        Me.ClientSize = New System.Drawing.Size(522, 275)
        Me.Controls.Add(Me.GroupBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Margin = New System.Windows.Forms.Padding(4, 5, 4, 5)
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "BGZ - Authentication System"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents textUsername As TextBox
    Friend WithEvents textPassword As TextBox
    Friend WithEvents LabelUser As Label
    Friend WithEvents LabelPass As Label
    Friend WithEvents Label1 As Label
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents buttonCancel As Button
    Friend WithEvents buttonLogin As Button
    Friend WithEvents Panel1 As Panel
    Friend WithEvents checkPass As CheckBox
End Class
