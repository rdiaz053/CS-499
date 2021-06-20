// Userlist data array for filling in info box
var userListData = [];
var thisUserObject;
var id;

// DOM Ready =============================================================
$(document).ready(function() {

  // Populate the user table on initial page load
  populateTable();
  
  // Username link click
  $('#userList table tbody').on('click', 'td a.linkshowuser', showUserInfo);
	
  // Add User button click
  $('#btnAddUser').on('click', addUser);

  // Delete User link click
  $('#userList table tbody').on('click', 'td a.linkdeleteuser', deleteUser);
  
  // Update button click
  $("#btnUpdate").on('click', populateUpdate);
  
  // Delete button click
  $("#btnDelete").on('click', deleteUser2);
  
  // Update User button click
  $("#btnUpdateUser").on('click', updateUser);
});

// Functions =============================================================

// Fill table with data
function populateTable() {

  // Empty content string
  var tableContent = '';

  // jQuery AJAX call for JSON
  $.getJSON( '/data/customers', function( data ) {
	  
	// Stick our user data array into a userlist variable in the global object
	userListData = data;
	
    // For each item in our JSON, add a table row and cells to the content string
    $.each(data, function(){
      tableContent += '<tr>';
	  tableContent += '<td><a href="#" class="linkshowuser" rel="' + this.first_name + '">Show</a></td>';
      tableContent += '<td>' + this.first_name + '</a></td>';
      tableContent += '<td>' + this.last_name + '</a></td>';
	  tableContent += '<td>' + this.Age + '</td>';
      tableContent += '<td>' + this.city + '</td>';
      tableContent += '<td>' + this.county + '</td>';
	  tableContent += '<td>' + this.state + '</td>';
	  tableContent += '<td>' + this.zip + '</td>';
      tableContent += '<td><a href="#" class="linkdeleteuser" rel="' + this._id + '">Delete</a></td>';
      tableContent += '</tr>';
    });

	// Update Customer Count
    $('#userCount').text("(" + userListData.length + ")");
	
    // Inject the whole content string into our existing HTML table
    $('#userList table tbody').html(tableContent);
  });

};

// Show User Info
function showUserInfo(event) {

  // Prevent Link from Firing
  event.preventDefault();

  // Retrieve username from link rel attribute
  var thisUserName = $(this).attr('rel');

  // Get Index of object based on id value
  var arrayPosition = userListData.map(function(arrayItem) { return arrayItem.first_name; }).indexOf(thisUserName);
  
  // Get our User Object
  thisUserObject = userListData[arrayPosition];

  // Populate Info Box
  $('#userInfoName').text(thisUserObject.first_name + ' ' + thisUserObject.last_name);
  $('#userInfoAge').text(thisUserObject.Age);
  $('#userInfoCity').text(thisUserObject.city);
  $('#userInfoCounty').text(thisUserObject.county);
  $('#userInfoState').text(thisUserObject.state);
  $('#userInfoZip').text(thisUserObject.zip);
  $('#userInfoResSpend').text('$' + thisUserObject.Restaurant);
  $('#userInfoResVisit').text(thisUserObject.RES_VISITS);
  $('#userInfoWebSpend').text('$' + thisUserObject.Webstore_Spend);
  $('#userInfoWebVisit').text(thisUserObject.WEB_VISITS);
  $('#userInfo3rdSpend').text('$' + thisUserObject.THIRD_SPEND);
  $('#userInfo3rdVisit').text(thisUserObject.THIRD_VISITS);
  $('#userInfoID').text(thisUserObject._id);
  
  $('html, body').animate({ scrollTop: 0 }, 'fast');
  // Populate Update Box
  //$('#inputFirstName').val(thisUserObject.first_name + ' ' + thisUserObject.last_name);
};

function clearUserInfo() {
  $('#userInfoName').text('');
  $('#userInfoAge').text('');
  $('#userInfoCity').text('');
  $('#userInfoCounty').text('');
  $('#userInfoState').text('');
  $('#userInfoZip').text('');
  $('#userInfoResSpend').text('');
  $('#userInfoResVisit').text('');
  $('#userInfoWebSpend').text('');
  $('#userInfoWebVisit').text('');
  $('#userInfo3rdSpend').text('');
  $('#userInfo3rdVisit').text('');
  $('#userInfoID').text('');
  thisUserObject = ''
}

// Update User
function updateUser(event){
	// Super basic validation - increase errorCount variable if any fields are blank
	var errorCount = 0;
	$('#addUser input').each(function(index, val) {
		if($(this).val() === '') { errorCount++; }
	});
	
	// Check and make sure errorCount's still at zero
	if(errorCount === 0) {
		
    var updateUser = {
		'_id': (id),
		'first_name': $('#addUser fieldset input#inputFirstName').val(),
		'last_name': $('#addUser fieldset input#inputLastName').val(),
		'Age': $('#addUser fieldset input#inputAge').val(),
		'city': $('#addUser fieldset input#inputCity').val(),
		'county': $('#addUser fieldset input#inputCounty').val(),
		'state': $('#addUser fieldset input#inputState').val(),
		'zip': $('#addUser fieldset input#inputZip').val(),
		'Restaurant': $('#addUser fieldset input#inputResSpend').val(),
		'RES_VISITS': $('#addUser fieldset input#inputResVisit').val(),
		'Webstore_Spend': $('#addUser fieldset input#inputWebSpend').val(),
		'WEB_VISITS': $('#addUser fieldset input#inputWebVisit').val(),
		'THIRD_SPEND': $('#addUser fieldset input#input3rdSpend').val(),
		'THIRD_VISITS': $('#addUser fieldset input#input3rdVisit').val()
    }	
	
	$.ajax({
		type: 'PUT',
		data: updateUser,
		url: '/data/updateUser/' + $(thisUserObject).attr('_id'),
		dataType: 'JSON'
    }).done(function( repsonse ) {
		alert("Customer Data Updated");
		// Clear the form inputs
		$('#addUser fieldset input').val('');
		// Update the table
		populateTable();
		// Scroll to bottom
		//$('html, body').animate({scrollTop: $(document).height()}, 'fast');
		clearUserInfo();
    });
  }
  else {
    // If errorCount is more than 0, error out
    alert('Please fill in all fields');
    return false;
  }
};

// Add User
function addUser(event) {
  event.preventDefault();

  // Super basic validation - increase errorCount variable if any fields are blank
  var errorCount = 0;
  $('#addUser input').each(function(index, val) {
    if($(this).val() === '') { errorCount++; }
  });

  // Check and make sure errorCount's still at zero
  if(errorCount === 0) {

    // If it is, compile all user info into one object
    var newUser = {
      'first_name': $('#addUser fieldset input#inputFirstName').val(),
      'last_name': $('#addUser fieldset input#inputLastName').val(),
      'Age': $('#addUser fieldset input#inputAge').val(),
      'city': $('#addUser fieldset input#inputCity').val(),
      'county': $('#addUser fieldset input#inputCounty').val(),
      'state': $('#addUser fieldset input#inputState').val(),
	  'zip': $('#addUser fieldset input#inputZip').val(),
      'Restaurant': $('#addUser fieldset input#inputResSpend').val(),
      'RES_VISITS': $('#addUser fieldset input#inputResVisit').val(),
      'Webstore_Spend': $('#addUser fieldset input#inputWebSpend').val(),
      'WEB_VISITS': $('#addUser fieldset input#inputWebVisit').val(),
      'THIRD_SPEND': $('#addUser fieldset input#input3rdSpend').val(),
	  'THIRD_VISITS': $('#addUser fieldset input#input3rdVisit').val()
    }

    // Use AJAX to post the object to our adduser service
    $.ajax({
      type: 'POST',
      data: newUser,
      url: '/data/addUser',
      dataType: 'JSON'
    }).done(function( response ) {

      // Check for successful (blank) response
      if (response.msg === '') {
		alert("Customer Data Added");
        // Clear the form inputs
        $('#addUser fieldset input').val('');

        // Update the table
        populateTable();
		
		// Scroll to bottom
		$('html, body').animate({scrollTop: $(document).height()}, 'fast');
      }
      else {

        // If something goes wrong, alert the error message that our service returned
        alert('Error: ' + response.msg);

      }
    });
  }
  else {
    // If errorCount is more than 0, error out
    alert('Please fill in all fields');
    return false;
  }
  
};

// Delete User
function deleteUser(event) {

  event.preventDefault();

  // Pop up a confirmation dialog
  var confirmation = confirm('Are you sure you want to delete this customer?');

  // Check and make sure the user confirmed
  if (confirmation === true) {

    // If they did, do our delete
    $.ajax({
      type: 'DELETE',
      url: '/data/deleteUser/' + $(this).attr('rel')
    }).done(function( response ) {

      // Check for a successful (blank) response
      if (response.msg === '') {
		  alert("Customer Data Deleted");
      }
      else {
        alert('Error: ' + response.msg);
      }

      // Update the table
      populateTable();
	
	  clearUserInfo();
    });

  }
  else {

    // If they said no to the confirm, do nothing
    return false;

  }

};

// Delete User
function deleteUser2(event) {

  event.preventDefault();

  // Pop up a confirmation dialog
  var confirmation = confirm('Are you sure you want to delete this customer?');

  // Check and make sure the user confirmed
  if (confirmation === true) {

    // If they did, do our delete
    $.ajax({
      type: 'DELETE',
      url: '/data/deleteUser/' + thisUserObject._id
    }).done(function( response ) {

      // Check for a successful (blank) response
      if (response.msg === '') {
		  alert("Customer Data Deleted");
      }
      else {
        alert('Error: ' + response.msg);
      }

      // Update the table
      populateTable();
	
	  clearUserInfo();
    });

  }
  else {

    // If they said no to the confirm, do nothing
    return false;

  }

};

function populateUpdate(event){
	// Populate Update Box
	id = thisUserObject._id;
	$('#inputFirstName').val(thisUserObject.first_name);
	$('#inputLastName').val(thisUserObject.last_name);
	$('#inputAge').val(thisUserObject.Age);
	$('#inputCity').val(thisUserObject.city);
	$('#inputCounty').val(thisUserObject.county);
	$('#inputState').val(thisUserObject.state);
	$('#inputZip').val(thisUserObject.zip);
	$('#inputResSpend').val(thisUserObject.Restaurant);
	$('#inputResVisit').val(thisUserObject.RES_VISITS);
	$('#inputWebSpend').val(thisUserObject.Webstore_Spend);
	$('#inputWebVisit').val(thisUserObject.WEB_VISITS);
	$('#input3rdSpend').val(thisUserObject.THIRD_SPEND);
	$('#input3rdVisit').val(thisUserObject.THIRD_VISITS);
};

function sortTable(f,n){
    var rows = $('#userList tbody tr').get();
    //$('#userInfoName').text(rows);
    rows.sort(function(a, b) {

        var A = getVal(a);
        var B = getVal(b);

        if(A < B) {
            return -1*f;
        }
        if(A > B) {
            return 1*f;
        }
        return 0;
    });

    function getVal(elm){
        var v = $(elm).children('td').eq(n).text().toUpperCase();
        if($.isNumeric(v)){
            v = parseInt(v,10);
        }
        return v;
    }

    $.each(rows, function(index, row) {
        $('#userList tbody').append(row);
    });

}

var f_first = -1; // flag to toggle the sorting order
var f_last = -1; // flag to toggle the sorting order
var f_age = -1; // flag to toggle the sorting order
var f_city = -1; // flag to toggle the sorting order
var f_county = -1; // flag to toggle the sorting order
var f_state = -1; // flag to toggle the sorting order
var f_zip = -1; // flag to toggle the sorting order

$("#first").click(function(){
    f_first *= -1; // toggle the sorting order
	if (f_first == 1) {
		$("#first").text("First Name ⯅");
    }
	else if (f_first == -1){
		$("#first").text("First Name ⯆");
    }
	else {
		$("#first").text("First Name ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_first,n);
});

$("#last").click(function(){
    f_last *= -1; // toggle the sorting order
	if (f_last == 1) {
		$("#last").text("Last Name ⯅");
    }
	else if (f_last == -1){
		$("#last").text("Last Name ⯆");
    }
	else {
		$("#last").text("Last Name ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_last,n);
});
$("#age").click(function(){
    f_age *= -1; // toggle the sorting order
	if (f_age == 1) {
		$("#age").text("Age ⯅");
    }
	else if (f_age == -1){
		$("#age").text("Age ⯆");
    }
	else {
		$("#age").text("Age ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_age,n);
});
$("#city").click(function(){
    f_city *= -1; // toggle the sorting order
	if (f_city == 1) {
		$("#city").text("City ⯅");
    }
	else if (f_city == -1){
		$("#city").text("City ⯆");
    }
	else {
		$("#city").text("City ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_city,n);
});
$("#county").click(function(){
    f_county *= -1; // toggle the sorting order
	if (f_county == 1) {
		$("#county").text("County ⯅");
    }
	else if (f_county == -1){
		$("#county").text("County ⯆");
    }
	else {
		$("#county").text("County ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_county,n);
});
$("#state").click(function(){
    f_state *= -1; // toggle the sorting order
	if (f_state == 1) {
		$("#state").text("State ⯅");
    }
	else if (f_state == -1){
		$("#state").text("State ⯆");
    }
	else {
		$("#state").text("State ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_state,n);
});
$("#zip").click(function(){
    f_zip *= -1; // toggle the sorting order
	if (f_zip == 1) {
		$("#zip").text("Zip Code ⯅");
    }
	else if (f_zip == -1){
		$("#zip").text("Zip Code ⯆");
    }
	else {
		$("#zip").text("Zip Code ⬧");
	}
    var n = $(this).prevAll().length;
    sortTable(f_zip,n);
});