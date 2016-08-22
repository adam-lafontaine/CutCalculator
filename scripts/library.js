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
