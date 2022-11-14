
function accepthref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
    
  var orderSelected = document.getElementById("orderList").value;
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=none";
  
  window.location.href = ref;
}

function acceptinghref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var itemList = document.getElementById("itemList").value;
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=accept&item=" + itemList;
  
  window.location.href = ref;
}
