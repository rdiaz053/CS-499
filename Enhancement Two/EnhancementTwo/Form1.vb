Public Class Form1
    'Global Variable Declarations
    Public Shared failedAttempts As Integer = 0 'Stores Number Failed Attempts
    Public Shared userInfo(2) As String         'Stores User Login Information
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub ButtonLogin_Click(sender As Object, e As EventArgs) Handles buttonLogin.Click
        ' Prevents code from executing if either text box is empty
        If textUsername.Text = "" Or textPassword.Text = "" Then
            Exit Sub
        End If

        ' Variable Declarations
        Dim fileReader As String            'Used to reads from role file
        Dim objReader As New System.IO.StreamReader(My.Computer.FileSystem.CurrentDirectory + "/credentials.txt") 'Used read credential file
        Dim textLine As String              'Used to store read line from credential file
        Dim checkCredentials(4) As String   'Used to store split line data
        Dim message As String               'Used to store message to display in MSgBox

        'Retrieves username and password from text boxes
        userInfo(0) = textUsername.Text
        userInfo(1) = textPassword.Text

        'Iterates through credentials file until EOF is reached or successful match occurs
        Do While objReader.Peek() <> -1 And (checkCredentials(0) <> userInfo(0))
            textLine = objReader.ReadLine()                                 'Reads line
            checkCredentials = Split(textLine, Chr(9))                      'Splits line data using tab character as a delimiter
            checkCredentials(2) = Replace(checkCredentials(2), """", "")    'Strips quotation marks from password
        Loop

        'If statement to handle login outcomes
        If userInfo(1) = checkCredentials(2) Then 'Valid Login Credentials:
            failedAttempts = 0  'Resets failed Attempts Counter
            Threading.Thread.Sleep(500) 'Sleep for 0.5 seconds

            'Reads contents of appropriate role file and displays to user
            fileReader = My.Computer.FileSystem.ReadAllText(My.Computer.FileSystem.CurrentDirectory + "\" + checkCredentials(3) + ".txt")
            MsgBox(fileReader, vbOKOnly, "BGZ - Authentication System")

            'Hides login form and shows management form
            userInfo(0) = checkCredentials(0)
            userInfo(1) = checkCredentials(3)
            Form2.Show()
            textUsername.Text = ""
            textPassword.Text = ""
            Me.Hide()

        Else 'Invalid Login Credentials:
            failedAttempts += 1 'Increment failed attempts counter

            'If statement to handle failed logon message:
            If failedAttempts < 3 Then  'Attempts Remaining
                'Notify user of unsuccessful logon attempt and number of attempts left
                message = "Invalid Credentials " + CStr(3 - failedAttempts) + " - Attempt(s) Left"
                MsgBox(message, vbOKOnly, "BGZ - Authentication System")
            Else
                'Notify user that max number of attempts has been reached
                message = "Maximum Number of Attempts Reached - Exiting Program"
                MsgBox(message, vbOKOnly, "BGZ - Authentication System")
                Me.Close()  'Exits Program
            End If

        End If

    End Sub

    Private Sub ButtonCancel_Click(sender As Object, e As EventArgs) Handles buttonCancel.Click
        Me.Close() 'Exits Program
    End Sub

    Private Sub checkPass_CheckedChanged(sender As Object, e As EventArgs) Handles checkPass.CheckedChanged
        'Allows user to hide or show password based on checkbox status
        If checkPass.Checked Then
            textPassword.PasswordChar = ""
        Else
            textPassword.PasswordChar = "●"
        End If
    End Sub
End Class
