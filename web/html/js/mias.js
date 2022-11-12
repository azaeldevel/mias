
function cmdhref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  
  var orderSelected = document.getElementById("orderList").value;
  var ref = "?station=" + station + "&order=" + orderSelected;
  
  var cmd = document.getElementById("cmd");
  cmd.href = ref;
}
