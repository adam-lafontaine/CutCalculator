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
    if(!inputValid())
      return;

    $('#UserInput').hide();

    let cutLoss = getFloatFromInput('#TextBoxCutLoss');

    let resultSetArray = sortLengths(getLengthGroups('Cut'), getLengthGroups('Stock'), cutLoss);
    for(let i = 0; i < resultSetArray.length; i++)
    {
      addResultSet(resultSetArray[i]);
    }

    $('#Results').show();
  });

  $('#ButtonReset').click(function(e)
  {
    resetInput();    
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

  //clear cut loss field
  $('#TextBoxCutLoss').val('0')
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
  let idx = getIntFromInput('#Hidden' + tag + 'Index');
  $('#Hidden' + tag + 'Index').val(idx + 1);
  createInputRow(tag + idx).appendTo('#' + tag + 'List');
}

//-------------------------------------------------

// removes the last row of input specified
// and decrements the coresponding index saved in the hidden field
function removeInputRow(tag)
{
  let idx = getIntFromInput('#Hidden' + tag + 'Index');

  if(idx > 1)
  {
    idx-= 1;
    $('#Row' + tag + idx).remove();
    $('#Hidden' + tag + 'Index').val(idx);
  }

}

//--------------------------------------------------

// creates an array of LengthGroups from input on the page
// tag = 'Cut' or 'Stock'
function getLengthGroups(tag)
{
  let result = [];
  let index = getIntFromInput('#Hidden' + tag + 'Index');
  for(let i = 0; i < index; i++)
  {
    let qty = getIntFromInput('#TextBoxQty' + tag + i);
    let length = getFloatFromInput('#TextBoxLength' + tag + i);
    let label = $('#TextBoxLabel' + tag + i).val();

    result.push(new LengthGroup(qty, length, label));
  }

  return result;
}

//***************** OUTPUT FUNCTIONS ***************************

// adds the values from a ResultSet object to the output on the page
function addResultSet(result_set)
{
  let idx = getIntFromInput('#HiddenResultSetIndex');
  $('#HiddenResultSetIndex').val(idx + 1);

  $("#ResultList").append(createResultSetDiv(result_set, idx));
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
  let row = $('<div/>',{'id':'Row' + tag, 'class': 'row'});
  let c1 = $('<div/>', {'class': 'col-xs-3 col-wide'});
  let c2 = $('<div/>', {'class': 'col-xs-4 col-wide'});
  let c3 = $('<div/>', {'class': 'col-xs-5 col-wide'});

  c1.append(createTextBox('TextBoxQty' + tag, 'Quantity').addClass("notblank posint notzero"));
  c2.append(createTextBox('TextBoxLength' + tag, 'Length').addClass("notblank posnumeric notzero"));
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
  let row = $('<div/>',{'class': 'row'});
  let c1 = $('<div/>', {'class': 'col-xs-4 col-wide', text: qty});
  let c2 = $('<div/>', {'class': 'col-xs-4 col-wide', text: length});
  let c3 = $('<div/>', {'class': 'col-xs-4 col-wide', text: label});

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
  let table = $('<table/>', {
    'id': 'ResultSet' + idx,
    'class': 'table table-bordered'
  });

  //heading
  let heading = $('<thead/>', {});
  heading.append(create3ColumnRow('<th/>', 'Quantity', 'Length', 'Label'));

  //body
  let body = $('<tbody/>', {});
  $.each(result_set.lengthGroupArray, function(index, group){
    body.append(create3ColumnRow('<td/>', group.quantity, group.groupLength, group.groupLabel));
  });

  //footer
  let footer = $('<tfoot/>', {'class': 'bold'});
  footer.append(create3ColumnRow('<td/>', 'Stock', result_set.stockLength.pieceLength, result_set.stockLength.pieceLabel));
  footer.append(create3ColumnRow('<td/>', 'Leftover', result_set.leftover, ''));

  table.append(heading);
  table.append(footer);
  table.append(body);

  return table;
}

//-----------------------------------

function create3ColumnRow(element, c1Text, c2Text, c3Text)
{
  let tableRow = $('<tr/>', {});

  let c1 = $(element,{text: c1Text});
  let c2 = $(element,{text: c2Text});
  let c3 = $(element,{text: c3Text});

  tableRow.append(c1);
  tableRow.append(c2);
  tableRow.append(c3);

  return tableRow;
}
