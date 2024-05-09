<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class fmMain
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
        Me.lvDetails = New System.Windows.Forms.ListView()
        Me.chParameters = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.chValue = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.tvDrones = New System.Windows.Forms.TreeView()
        Me.btStop = New System.Windows.Forms.Button()
        Me.btStart = New System.Windows.Forms.Button()
        Me.btClear = New System.Windows.Forms.Button()
        Me.lbLog = New System.Windows.Forms.ListBox()
        Me.SuspendLayout()
        '
        'lvDetails
        '
        Me.lvDetails.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.chParameters, Me.chValue})
        Me.lvDetails.FullRowSelect = True
        Me.lvDetails.GridLines = True
        Me.lvDetails.HideSelection = False
        Me.lvDetails.Location = New System.Drawing.Point(206, 41)
        Me.lvDetails.MultiSelect = False
        Me.lvDetails.Name = "lvDetails"
        Me.lvDetails.Size = New System.Drawing.Size(729, 459)
        Me.lvDetails.TabIndex = 9
        Me.lvDetails.UseCompatibleStateImageBehavior = False
        Me.lvDetails.View = System.Windows.Forms.View.Details
        '
        'chParameters
        '
        Me.chParameters.Text = "Parameter"
        Me.chParameters.Width = 150
        '
        'chValue
        '
        Me.chValue.Text = "Value"
        Me.chValue.Width = 540
        '
        'tvDrones
        '
        Me.tvDrones.FullRowSelect = True
        Me.tvDrones.HideSelection = False
        Me.tvDrones.Location = New System.Drawing.Point(12, 41)
        Me.tvDrones.Name = "tvDrones"
        Me.tvDrones.Size = New System.Drawing.Size(188, 459)
        Me.tvDrones.TabIndex = 8
        '
        'btStop
        '
        Me.btStop.Location = New System.Drawing.Point(93, 12)
        Me.btStop.Name = "btStop"
        Me.btStop.Size = New System.Drawing.Size(75, 23)
        Me.btStop.TabIndex = 7
        Me.btStop.Text = "Stop"
        Me.btStop.UseVisualStyleBackColor = True
        '
        'btStart
        '
        Me.btStart.Location = New System.Drawing.Point(12, 12)
        Me.btStart.Name = "btStart"
        Me.btStart.Size = New System.Drawing.Size(75, 23)
        Me.btStart.TabIndex = 6
        Me.btStart.Text = "Start"
        Me.btStart.UseVisualStyleBackColor = True
        '
        'btClear
        '
        Me.btClear.Location = New System.Drawing.Point(860, 506)
        Me.btClear.Name = "btClear"
        Me.btClear.Size = New System.Drawing.Size(75, 23)
        Me.btClear.TabIndex = 11
        Me.btClear.Text = "Clear"
        Me.btClear.UseVisualStyleBackColor = True
        '
        'lbLog
        '
        Me.lbLog.FormattingEnabled = True
        Me.lbLog.Location = New System.Drawing.Point(12, 535)
        Me.lbLog.Name = "lbLog"
        Me.lbLog.Size = New System.Drawing.Size(923, 121)
        Me.lbLog.TabIndex = 10
        '
        'fmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(947, 668)
        Me.Controls.Add(Me.lvDetails)
        Me.Controls.Add(Me.tvDrones)
        Me.Controls.Add(Me.btStop)
        Me.Controls.Add(Me.btStart)
        Me.Controls.Add(Me.btClear)
        Me.Controls.Add(Me.lbLog)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Name = "fmMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Drone Remote ID Receiver"
        Me.ResumeLayout(False)

    End Sub

    Private WithEvents lvDetails As ListView
    Private WithEvents chParameters As ColumnHeader
    Private WithEvents chValue As ColumnHeader
    Private WithEvents tvDrones As TreeView
    Private WithEvents btStop As Button
    Private WithEvents btStart As Button
    Private WithEvents btClear As Button
    Private WithEvents lbLog As ListBox
End Class
