
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

function restoreOrderhref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
    
  var orderSelected = document.getElementById("restoreOrderList").value;
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=none&restoring";
  
  window.location.href = ref;
}

function restoreStephref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var restoreStep = document.getElementById("restoreStepList").value;
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&restoring&step=" + restoreStep;
  
  window.location.href = ref;
}
function toPrepare() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
    
  var cmdPreparing = document.getElementById("cmdPreparing");
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=prepare&item="+ item; 
  
  cmdPreparing.href = ref;
}
function toPrepared() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
    
  var cmdPrepared = document.getElementById("cmdPrepared");
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=prepared&item="+ item; 
  
  cmdPrepared.href = ref;
}
function toBaking() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
    
  var cmdBaking = document.getElementById("cmdBaking");
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=baking&item="+ item; 
  
  cmdBaking.href = ref;
}
function toBaked() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
    
  var cmdBaked = document.getElementById("cmdBaked");
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=baked&item="+ item; 
  
  cmdBaked.href = ref;
}
function toFinalized() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
    
  var cmdFinalized = document.getElementById("cmdFinalized");
  var ref = "/application.cgi?station=" + station + "&order=" + orderSelected + "&step=finalized&item="+ item; 
  
  cmdFinalized.href = ref;
}
function toBegin() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
    
  var cmdBegin = document.getElementById("cmdBegin");
  var ref = "/application.cgi?station=" + station + "&step=none"; 
  
  cmdBegin.href = ref;
}
