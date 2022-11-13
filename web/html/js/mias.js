
function stephref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  
  var orderSelected = document.getElementById("orderList").value;
  var ref = "?station=" + station + "&order=" + orderSelected + "&step=accept";
  
  var stepcmd = document.getElementById("stepcmd");
  stepcmd.href = ref;
}
