/*
page.js - functionality that is directly related to user interface
*/

// Function that runs when page is loaded
$(function()
{
  // set up page
  $('#Results').hide();

  resetInput();

  // event handlers
  $('#ButtonAddCutRow').click(function(e)
  {
    addInputRow('Cut');
  });

  //-----------------------------------------------------

  $('#ButtonAddStockRow').click(function(e)
  {
    addInputRow('Stock');
  });

  //------------------------------------------------------

  $('#ButtonRemoveStockRow').click(function(e)
  {
    removeInputRow('Stock');
  });

  //------------------------------------------------------

  $('#ButtonRemoveCutRow').click(function(e)
  {
    removeInputRow('Cut');
  });

  //-----------------------------------------------------

  // runs the sorting algorithm and displays in #Results
  $('#ButtonAction').click(function(e)
  {
    $('#UserInput').hide();

    var resultSetArray = sortLengths(getLengthGroups('Cut'), getLengthGroups('Stock'));
    for(var i = 0; i < resultSetArray.length; i++)
    {
      addResultSet(resultSetArray[i]);
    }

    $('#Results').show();
  });

  //------------------------------------------------------

  $('#ButtonRestart').click(function(e)
  {
    resetInput();
    $('#Results').hide();
    resetResults();
    $('#UserInput').show();
  });

  //-------------------------------------------------------

});


//******************* INPUT FUNCTIONS *****************************

function resetInput()
{
  // clear example code
  removeAllInputRows('Cut');
  removeAllInputRows('Stock');

  // begin with one row for input
  addInputRow('Cut');
  addInputRow('Stock');
}

//-------------------------------------------------------

function resetResults()
{
  $('#ResultList').html("");
  $('#HiddenResultSetIndex').val(0);
}

//--------------------------------------------------

// clears the specified list of all rows for input
function removeAllInputRows(tag)
{
  $('#Hidden' + tag + 'Index').val(0);
  $('#' + tag + 'List').html("");
}

//---------------------------------------------------

// adds a row for the input specified
// and increments the coresponding index saved in the hidden field
function addInputRow(tag)
{
  var idx = getIntFromInput('#Hidden' + tag + 'Index');
  $('#Hidden' + tag + 'Index').val(idx + 1);
  createInputRow(tag + idx).appendTo('#' + tag + 'List');
}

//-------------------------------------------------

// removes the last row of input specified
// and decrements the coresponding index saved in the hidden field
function removeInputRow(tag)
{
  var idx = getIntFromInput('#Hidden' + tag + 'Index') - 1;
  $('#Row' + tag + idx).remove();
  $('#Hidden' + tag + 'Index').val(idx);
}

//--------------------------------------------------

// gets an int value from an input element
function getIntFromInput(selector)
{
  return $(selector).val() == "" ? 0 : parseInt($(selector).val());
}

//---------------------------------------------

// gets a float value from an input element
function getFloatFromInput(selector)
{
  return $(selector).val() == "" ? 0 : parseFloat($(selector).val());
}

//---------------------------------------------

// creates and array of LengthGroups from input on the page
// tag = 'Cut' or 'Stock'
function getLengthGroups(tag)
{
  var result = [];
  var index = getIntFromInput('#Hidden' + tag + 'Index');
  for(var i = 0; i < index; i++)
  {
    var qty = getIntFromInput('#TextBoxQty' + tag + i);
    var length = getFloatFromInput('#TextBoxLength' + tag + i);
    var label = $('#TextBoxLabel' + tag + i).val();

    result.push(new LengthGroup(qty, length, label));
  }

  return result;
}

//***************** OUTPUT FUNCTIONS ***************************

// adds the values from a ResultSet object to the output on the page
function addResultSet(result_set)
{
  var div = $('<div/>',{'class': 'row'});

  var idx = getIntFromInput('#HiddenResultSetIndex');
  $('#HiddenResultSetIndex').val(idx + 1);

  div.append(createResultSetDiv(result_set, idx));

  div.appendTo('#ResultList');
}

//--------------------------------------------

//******************* UTILITY FUNCTIONS *************************

// creates a text box with an id and a placeholder
function createTextBox(id, placeholder)
{
   return $('<input/>',{
    'type': 'text',
    'class': 'form-control',
    'id': id,
    'name': id,
    'placeholder': placeholder
  });
}

//------------------------------------------------------------

// creates a new row for input
// tag = used to uniquely identify id attributes
function createInputRow(tag)
{
  var row = $('<div/>',{'id':'Row' + tag, 'class': 'row'});
  var c1 = $('<div/>', {'class': 'col-xs-4'});
  var c2 = $('<div/>', {'class': 'col-xs-4'});
  var c3 = $('<div/>', {'class': 'col-xs-4'});

  c1.append(createTextBox('TextBoxQty' + tag, 'Quantity'));
  c2.append(createTextBox('TextBoxLength' + tag, 'Length'));
  c3.append(createTextBox('TextBoxLabel' + tag, 'Label'));

  row.append(c1);
  row.append(c2);
  row.append(c3);

  return row;
}

//------------------------------------------------------------

// creates a new row within a ResultSet to display
function createResultRow(qty, length, label)
{
  var row = $('<div/>',{'class': 'row'});
  var c1 = $('<div/>', {'class': 'col-xs-4', text: qty});
  var c2 = $('<div/>', {'class': 'col-xs-4', text: length});
  var c3 = $('<div/>', {'class': 'col-xs-4', text: label});

  row.append(c1);
  row.append(c2);
  row.append(c3);

  return row;
}

//------------------------------------------

// creates a div to diplay a ResultSet object
// idx = unique identifier for div
function createResultSetDiv(result_set, idx)
{
  var div = $('<div/>', {
    'id': 'ResultSet' + idx,
    'class': 'col-xs-6 panel-group'
  });

  // heading
  var heading = $('<div/>',{
    'class': 'panel-heading'
  });

  var titleRow = create3ColumnRow('Quantity', 'Length', 'Label');
  heading.append(titleRow);


  // list
  var list = $('<div/>', {
    'id': 'ResultList' + idx,
    'class': 'panel'
  });

  for(var i = 0; i < result_set.lengthGroupArray.length; i++)
  {
    var group = result_set.lengthGroupArray[i];
    list.append(create3ColumnRow(group.quantity, group.groupLength, group.groupLabel));
  }

  // footer
  var footer = $('<div/>',{
    'class': 'panel-footer'
  });

  var stockRow = create3ColumnRow('Stock', result_set.stockLength.pieceLength, result_set.stockLength.pieceLabel);
  footer.append(stockRow);

  var leftoverRow = create3ColumnRow('Leftover', result_set.leftover, '');
  footer.append(leftoverRow);

  // complete div
  div.append(heading);
  div.append(list);
  div.append(footer);

  return div;
}

//-----------------------------------

function create3ColumnRow(c1Text, c2Text, c3Text)
{
  var row = $('<div/>',{'class': 'row'});

  var c1 = $('<div/>',{'class': 'col-xs-4', text: c1Text});
  var c2 = $('<div/>',{'class': 'col-xs-4', text: c2Text});
  var c3 = $('<div/>',{'class': 'col-xs-4', text: c3Text});

  row.append(c1);
  row.append(c2);
  row.append(c3);

  return row;
}

//----------------------------------

function createLeftoverRow(length)
{
  var row = $('<div/>',{'class': 'row'});
  var c1 = $('<div/>', {'class': 'col-xs-4', text: 'Leftover:'});

  var c2 = $('<div/>', {'class': 'col-xs-4', text: length});

  row.append(c1);
  row.append(c2);

  return row;
}
