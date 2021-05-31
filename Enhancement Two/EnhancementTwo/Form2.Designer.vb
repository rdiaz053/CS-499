<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form2
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
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
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form2))
        Me.Label1 = New System.Windows.Forms.Label()
        Me.buttonLoad = New System.Windows.Forms.Button()
        Me.labelSort = New System.Windows.Forms.Label()
        Me.listSort = New System.Windows.Forms.ListBox()
        Me.labelListview = New System.Windows.Forms.Label()
        Me.listAnimalInfo = New System.Windows.Forms.ListView()
        Me.columnName = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.columnSpecies = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.columnAge = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.columnStatus = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.buttonLogout = New System.Windows.Forms.Button()
        Me.labelRole = New System.Windows.Forms.Label()
        Me.labelName = New System.Windows.Forms.Label()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 26.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(109, 26)
        Me.Label1.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(260, 39)
        Me.Label1.TabIndex = 10
        Me.Label1.Text = "Big Gorilla Zoo"
        '
        'buttonLoad
        '
        Me.buttonLoad.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.buttonLoad.Location = New System.Drawing.Point(353, 188)
        Me.buttonLoad.Name = "buttonLoad"
        Me.buttonLoad.Size = New System.Drawing.Size(93, 82)
        Me.buttonLoad.TabIndex = 2
        Me.buttonLoad.Text = "Load Data From File"
        Me.buttonLoad.UseVisualStyleBackColor = True
        '
        'labelSort
        '
        Me.labelSort.AutoSize = True
        Me.labelSort.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.labelSort.Location = New System.Drawing.Point(349, 74)
        Me.labelSort.Name = "labelSort"
        Me.labelSort.Size = New System.Drawing.Size(73, 20)
        Me.labelSort.TabIndex = 5
        Me.labelSort.Text = "Sort By:"
        '
        'listSort
        '
        Me.listSort.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.listSort.FormattingEnabled = True
        Me.listSort.ItemHeight = 20
        Me.listSort.Items.AddRange(New Object() {"Name", "Species", "Age", "Status"})
        Me.listSort.Location = New System.Drawing.Point(353, 98)
        Me.listSort.Name = "listSort"
        Me.listSort.Size = New System.Drawing.Size(93, 84)
        Me.listSort.TabIndex = 3
        '
        'labelListview
        '
        Me.labelListview.AutoSize = True
        Me.labelListview.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.labelListview.Location = New System.Drawing.Point(14, 74)
        Me.labelListview.Name = "labelListview"
        Me.labelListview.Size = New System.Drawing.Size(160, 20)
        Me.labelListview.TabIndex = 8
        Me.labelListview.Text = "Animal Information"
        '
        'listAnimalInfo
        '
        Me.listAnimalInfo.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnName, Me.columnSpecies, Me.columnAge, Me.columnStatus})
        Me.listAnimalInfo.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.listAnimalInfo.HideSelection = False
        Me.listAnimalInfo.Location = New System.Drawing.Point(15, 98)
        Me.listAnimalInfo.Name = "listAnimalInfo"
        Me.listAnimalInfo.Size = New System.Drawing.Size(326, 172)
        Me.listAnimalInfo.TabIndex = 4
        Me.listAnimalInfo.UseCompatibleStateImageBehavior = False
        Me.listAnimalInfo.View = System.Windows.Forms.View.Details
        '
        'columnName
        '
        Me.columnName.Text = "Name"
        Me.columnName.Width = 84
        '
        'columnSpecies
        '
        Me.columnSpecies.Text = "Species"
        Me.columnSpecies.Width = 98
        '
        'columnAge
        '
        Me.columnAge.Text = "Age"
        Me.columnAge.Width = 49
        '
        'columnStatus
        '
        Me.columnStatus.Text = "Status"
        Me.columnStatus.Width = 70
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.buttonLogout)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.listAnimalInfo)
        Me.GroupBox1.Controls.Add(Me.labelListview)
        Me.GroupBox1.Controls.Add(Me.listSort)
        Me.GroupBox1.Controls.Add(Me.labelSort)
        Me.GroupBox1.Controls.Add(Me.buttonLoad)
        Me.GroupBox1.Location = New System.Drawing.Point(11, 12)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(458, 280)
        Me.GroupBox1.TabIndex = 11
        Me.GroupBox1.TabStop = False
        '
        'buttonLogout
        '
        Me.buttonLogout.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.buttonLogout.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.buttonLogout.Location = New System.Drawing.Point(5, 10)
        Me.buttonLogout.Name = "buttonLogout"
        Me.buttonLogout.Size = New System.Drawing.Size(60, 22)
        Me.buttonLogout.TabIndex = 12
        Me.buttonLogout.Text = "Logout"
        Me.buttonLogout.UseVisualStyleBackColor = True
        '
        'labelRole
        '
        Me.labelRole.AutoSize = True
        Me.labelRole.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.labelRole.Location = New System.Drawing.Point(17, 3)
        Me.labelRole.Name = "labelRole"
        Me.labelRole.Size = New System.Drawing.Size(71, 13)
        Me.labelRole.TabIndex = 12
        Me.labelRole.Text = "Logged in as:"
        '
        'labelName
        '
        Me.labelName.AutoSize = True
        Me.labelName.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.labelName.Location = New System.Drawing.Point(86, 3)
        Me.labelName.Name = "labelName"
        Me.labelName.Size = New System.Drawing.Size(35, 13)
        Me.labelName.TabIndex = 13
        Me.labelName.Text = "Name"
        '
        'Form2
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.CancelButton = Me.buttonLogout
        Me.ClientSize = New System.Drawing.Size(481, 298)
        Me.Controls.Add(Me.labelName)
        Me.Controls.Add(Me.labelRole)
        Me.Controls.Add(Me.GroupBox1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Form2"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "BGZ - Management System"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As Label
    Friend WithEvents buttonLoad As Button
    Friend WithEvents labelSort As Label
    Friend WithEvents listSort As ListBox
    Friend WithEvents labelListview As Label
    Friend WithEvents listAnimalInfo As ListView
    Friend WithEvents columnName As ColumnHeader
    Friend WithEvents columnSpecies As ColumnHeader
    Friend WithEvents columnAge As ColumnHeader
    Friend WithEvents columnStatus As ColumnHeader
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents buttonLogout As Button
    Friend WithEvents labelRole As Label
    Friend WithEvents labelName As Label
End Class
