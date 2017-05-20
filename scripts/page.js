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
    addCutRow();
  });

  //-----------------------------------------------------

  $('#ButtonAddStockRow').click(function(e)
  {
    addStockRow();
  });

  //------------------------------------------------------

  $('#ButtonRemoveStockRow').click(function(e)
  {
    removeStockRow();
  });

  //------------------------------------------------------

  $('#ButtonRemoveCutRow').click(function(e)
  {
    removeCutRow();
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
  removeAllInputRows();

  // begin with one row for input
  addCutRow();
  addStockRow();

  //clear cut loss field
  $('#TextBoxCutLoss').val('0');

}

//-------------------------------------

function removeAllInputRows()
{
  $('#HiddenCutIndex').val(0);
  $('#CutList').html("");
  $('#HiddenStockIndex').val(0);
  $('#StockList').html("");

  setState({
    CutIndex: 0,
    StockIndex: 0,
    ResultSetIndex: 0,
    TotalStock: 0,
    TotalCut: 0
  });
}

//-------------------------------------------------------

function resetResults()
{
  $('#ResultList').html("");

  setState({
    ResultSetIndex: 0
  });
}

//---------------------------------------------------

function addCutRow()
{
  let idx = getState().CutIndex + 1;
  createInputRow("Cut" + idx).appendTo('#CutList');

  setState({CutIndex: idx});
}

//---------------------------------------------

function addStockRow()
{
  let idx = getState().StockIndex + 1;
  createInputRow("Stock" + idx).appendTo('#StockList');

  setState({StockIndex: idx});
}

//-------------------------------------------------

// removes the last cut row
// and decrements the coresponding state variable
function removeCutRow()
{
  let idx = getState().CutIndex;

  if(idx > 1)
  {
    idx-= 1;
    $('#RowCut' + idx).remove();
    setState({CutIndex: idx});
  }

}

//--------------------------------------------------

// removes the last cut row
// and decrements the coresponding state variable
function removeStockRow()
{
  let idx = getState().StockIndex;

  if(idx > 1)
  {
    idx-= 1;
    $('#RowStock' + idx).remove();
    setState({StockIndex: idx});
  }

}

//--------------------------------------------------

// creates an array of LengthGroups from input on the page
// tag = 'Cut' or 'Stock'
function getLengthGroups(tag)
{
  let result = [];
  let key = tag + "Index";
  let index = getState()[key];
  for(let i = 1; i <= index; i++)
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
  let idx = getState().ResultSetIndex;

  $("#ResultList").append(createResultSetDiv(result_set, idx));
  setState({ResultSetIndex: idx + 1});
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

//--------------------------------------

function setState(params)
{
  let state = JSON.parse($('#State').val());
  for(var p in params)
    state[p] = params[p];

  $('#State').val(JSON.stringify(state));
}

//---------------------------------------

function getState()
{
  return JSON.parse($('#State').val());
}
