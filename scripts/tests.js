/*
file used for test input
*/
$(function()
{
  cutGroupArray = [];
  cutGroupArray.push(new LengthGroup(3, 10, 'short'));
  cutGroupArray.push(new LengthGroup(3, 48, 'long'));
  cutGroupArray.push(new LengthGroup(3, 30, 'medium'));

  stockGroupArray = [];
  stockGroupArray.push(new LengthGroup(10, 100, '10ft'));

  enterTestData(cutGroupArray, stockGroupArray);

});

//************ FOR TESTING *****************************************

function enterTestData(cutGroupArray, stockGroupArray)
{
  removeAllInputRows('Cut');
  removeAllInputRows('Stock');

  for(var i = 0; i < cutGroupArray.length; i++)
  {
    addInputRow('Cut');
    $('#TextBoxQtyCut' + i).val(cutGroupArray[i].quantity);
    $('#TextBoxLengthCut' + i).val(cutGroupArray[i].groupLength);
    $('#TextBoxLabelCut' + i).val(cutGroupArray[i].groupLabel);
  }

  for(var i = 0; i < stockGroupArray.length; i++)
  {
    addInputRow('Stock');
    $('#TextBoxQtyStock' + i).val(stockGroupArray[i].quantity);
    $('#TextBoxLengthStock' + i).val(stockGroupArray[i].groupLength);
    $('#TextBoxLabelStock' + i).val(stockGroupArray[i].groupLabel);
  }

}
