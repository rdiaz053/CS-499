Public Class Form2
    'Global Variable Declarations
    Public Structure animal
        Public animalName As String
        Public animalSpecies As String
        Public animalAge As Integer
        Public animalStatus As String
    End Structure
    Public animals As New ArrayList
    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        labelName.Text = Form1.userInfo(0) + ", " + Form1.userInfo(1)

    End Sub

    Private Sub Form2_FormClosing(sender As Object, e As EventArgs) Handles MyBase.FormClosing
        'Opens Form1 when closed
        Form1.Show()
    End Sub

    Private Sub ButtonLoad_Click(sender As Object, e As EventArgs) Handles buttonLoad.Click
        Dim objReader As New System.IO.StreamReader(My.Computer.FileSystem.CurrentDirectory + "/animals.txt") 'Used read animals file
        Dim textLine As String      'Stores read line
        Dim animalInfo(4) As String 'Stores split line data
        Dim newAnimal As animal     'Create new animal struct

        'Ensure arraylist and listview are empty
        animals.Clear()

        'Iterates through animals file until EOF is reached
        Do While objReader.Peek() <> -1
            textLine = objReader.ReadLine()         'Reads line
            animalInfo = Split(textLine, Chr(9))    'Splits line data using tab character as a delimiter

            'Create new animal struct from read data
            newAnimal.animalName = animalInfo(0)
            newAnimal.animalSpecies = animalInfo(1)
            newAnimal.animalAge = CInt(animalInfo(2))
            newAnimal.animalStatus = animalInfo(3)

            'Adds struct to arraylist
            animals.Add(newAnimal)
        Loop

        'Refreshes listview control
        addItems()

    End Sub

    Private Sub ListSort_SelectedIndexChanged(sender As Object, e As EventArgs) Handles listSort.SelectedIndexChanged
        'Calls bubbleSort sub and passes selected item
        bubbleSort(listSort.SelectedItem)
    End Sub

    Sub addItems()
        'Clears listview control
        listAnimalInfo.Items.Clear()

        'Iterates through the arraylist and adds items to the listview
        For Each item In animals
            Dim otherItems As String() = {item.animalSpecies, CStr(item.animalAge), item.AnimalStatus}
            listAnimalInfo.Items.Add(item.animalName).SubItems.AddRange(otherItems)
        Next
    End Sub

    Sub bubbleSort(type As String)
        'Variable declarations
        Dim i As Integer = 0    'Used for iteration
        Dim tempArray(animals.Count - 1) As animal 'Stores arraylist data for sorting

        For Each item In animals
            tempArray(i) = item
            i += 1
        Next

        'Selects property to sort based on listSort selection
        Select Case type
            Case "Name"     'Sorts by Name
                For i = 0 To (animals.Count) Step 1
                    For j = (animals.Count - 1) To i + 1 Step -1
                        If (tempArray(j).animalName < tempArray(j - 1).animalName) Then
                            Dim temp As animal = tempArray(j)
                            tempArray(j) = tempArray(j - 1)
                            tempArray(j - 1) = temp
                        End If
                    Next
                Next
            Case "Species"  'Sorts by Species
                For i = 0 To (animals.Count) Step 1
                    For j = (animals.Count - 1) To i + 1 Step -1
                        If (tempArray(j).animalSpecies < tempArray(j - 1).animalSpecies) Then
                            Dim temp As animal = tempArray(j)
                            tempArray(j) = tempArray(j - 1)
                            tempArray(j - 1) = temp
                        End If
                    Next
                Next
            Case "Age"      'Sorts by Age
                For i = 0 To (animals.Count) Step 1
                    For j = (animals.Count - 1) To i + 1 Step -1
                        If (tempArray(j).animalAge < tempArray(j - 1).animalAge) Then
                            Dim temp As animal = tempArray(j)
                            tempArray(j) = tempArray(j - 1)
                            tempArray(j - 1) = temp
                        End If
                    Next
                Next
            Case "Status"   'Sorts by Status
                For i = 0 To (animals.Count) Step 1
                    For j = (animals.Count - 1) To i + 1 Step -1
                        If (tempArray(j).animalStatus < tempArray(j - 1).animalStatus) Then
                            Dim temp As animal = tempArray(j)
                            tempArray(j) = tempArray(j - 1)
                            tempArray(j - 1) = temp
                        End If
                    Next
                Next
        End Select

        'Clears arraylist and repopulates using sorted data from tempArray
        animals.Clear()
        For Each item In tempArray
            animals.Add(item)
        Next

        'Refreshes listview control
        addItems()
    End Sub

    Private Sub ButtonLogout_Click(sender As Object, e As EventArgs) Handles buttonLogout.Click
        'Closes form
        Me.Close()
    End Sub

End Class