

//************* funtions *********************

function inputValid()
{
  $(".invalid").each(function(){
    $(this).removeClass("invalid");
  });

  var result = true;

  if(!validateNotBlank())
    result = false;
  if(!validatePosInt())
    result = false;
  if(!validatePosNumeric())
    result = false;

  return result;
}

//---------------------------------

function validatePosNumeric()
{
  var result = true;

  $(".posnumeric").each(function(){
    var value = $(this).val();
    if(!isPosNumeric(value))
    {
      $(this).addClass("invalid");
      result = false;
    }
  });

  return result;
}

//-------------------------------

function validatePosInt()
{
  var result = true;

  $(".posint").each(function(){
    var value = $(this).val();
    if(!isPosInt(value))
    {
      $(this).addClass("invalid");
      result = false;
    }
  });

  return result;
}

//------------------------------

function validateNotBlank()
{
  var result = true;
  $(".notblank").each(function(){
    if($(this).val() == "")
    {
      $(this).addClass("invalid");
      result = false;
    }
  });

  return result;
}

//************************************************

// positive integer, only digits
function isPosInt(n)
{
    return (n + "").match(/^\d+$/);
}

//-----------------------------------

function isPosNumeric(n)
{
  return (n + "").match(/^\d+.?\d+$/) || isPosInt(n);
}
