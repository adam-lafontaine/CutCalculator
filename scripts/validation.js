

//************* funtions *********************

function inputValid()
{
  $(".invalid").each(function(){
    $(this).removeClass("invalid");
  });

  if(!validateNotBlank())
    return false;
  if(!validatePosInt())
    return false;
  if(!validatePosNumeric())
    return false;
  if(!validateNotZero())
    return false;

  return true;
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

//---------------------------------------

function validateNotZero()
{
  var result = true;

  $(".notzero").each(function(){
    var value = $(this).val();
    if(isZero(value))
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

//-------------------------------------

function isZero(n)
{
  return (n + "").match(/^[0]+$/) || (n + "").match(/^[0]+.[0]+$/);
}
