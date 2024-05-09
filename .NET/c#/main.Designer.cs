namespace DroneRemoteIdCSharp
{
    partial class fmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btStart = new System.Windows.Forms.Button();
            this.btStop = new System.Windows.Forms.Button();
            this.tvDrones = new System.Windows.Forms.TreeView();
            this.lvDetails = new System.Windows.Forms.ListView();
            this.chParameters = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chValue = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lbLog = new System.Windows.Forms.ListBox();
            this.btClear = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btStart
            // 
            this.btStart.Location = new System.Drawing.Point(12, 12);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(75, 23);
            this.btStart.TabIndex = 0;
            this.btStart.Text = "Start";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btStartClick);
            // 
            // btStop
            // 
            this.btStop.Location = new System.Drawing.Point(93, 12);
            this.btStop.Name = "btStop";
            this.btStop.Size = new System.Drawing.Size(75, 23);
            this.btStop.TabIndex = 1;
            this.btStop.Text = "Stop";
            this.btStop.UseVisualStyleBackColor = true;
            this.btStop.Click += new System.EventHandler(this.btStopClick);
            // 
            // tvDrones
            // 
            this.tvDrones.FullRowSelect = true;
            this.tvDrones.HideSelection = false;
            this.tvDrones.Location = new System.Drawing.Point(12, 41);
            this.tvDrones.Name = "tvDrones";
            this.tvDrones.Size = new System.Drawing.Size(188, 459);
            this.tvDrones.TabIndex = 2;
            this.tvDrones.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvDronesAfterSelect);
            // 
            // lvDetails
            // 
            this.lvDetails.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.chParameters,
            this.chValue});
            this.lvDetails.FullRowSelect = true;
            this.lvDetails.GridLines = true;
            this.lvDetails.HideSelection = false;
            this.lvDetails.Location = new System.Drawing.Point(206, 41);
            this.lvDetails.MultiSelect = false;
            this.lvDetails.Name = "lvDetails";
            this.lvDetails.Size = new System.Drawing.Size(729, 459);
            this.lvDetails.TabIndex = 3;
            this.lvDetails.UseCompatibleStateImageBehavior = false;
            this.lvDetails.View = System.Windows.Forms.View.Details;
            // 
            // chParameters
            // 
            this.chParameters.Text = "Parameter";
            this.chParameters.Width = 150;
            // 
            // chValue
            // 
            this.chValue.Text = "Value";
            this.chValue.Width = 540;
            // 
            // lbLog
            // 
            this.lbLog.FormattingEnabled = true;
            this.lbLog.Location = new System.Drawing.Point(12, 535);
            this.lbLog.Name = "lbLog";
            this.lbLog.Size = new System.Drawing.Size(923, 121);
            this.lbLog.TabIndex = 4;
            // 
            // btClear
            // 
            this.btClear.Location = new System.Drawing.Point(860, 506);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(75, 23);
            this.btClear.TabIndex = 5;
            this.btClear.Text = "Clear";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClearClick);
            // 
            // fmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(947, 668);
            this.Controls.Add(this.btClear);
            this.Controls.Add(this.lbLog);
            this.Controls.Add(this.lvDetails);
            this.Controls.Add(this.tvDrones);
            this.Controls.Add(this.btStop);
            this.Controls.Add(this.btStart);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "fmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Drone Remote ID Receiver";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.fmMainFormClosed);
            this.Load += new System.EventHandler(this.fmMain_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.Button btStop;
        private System.Windows.Forms.TreeView tvDrones;
        private System.Windows.Forms.ListView lvDetails;
        private System.Windows.Forms.ColumnHeader chParameters;
        private System.Windows.Forms.ColumnHeader chValue;
        private System.Windows.Forms.ListBox lbLog;
        private System.Windows.Forms.Button btClear;
    }
}

