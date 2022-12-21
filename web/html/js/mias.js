
function accepthref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var session = urlParams.get("session");
    
  var orderSelected = document.getElementById("orderList").value;
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=none&session=" + session;
  
  window.location.href = ref;
}

function acceptinghref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var itemList = document.getElementById("itemList").value;
  var session = urlParams.get("session");

  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=accept&item=" + itemList + "&session=" + session;
  
  window.location.href = ref;
}

function restoreOrderhref() 
{
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var session = urlParams.get("session");
    
  var orderSelected = document.getElementById("restoreOrderList").value;
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=none&restoring&session=" + session;
  
  window.location.href = ref;
}

function restoreStephref() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var restoreStep = document.getElementById("restoreStepList").value;
  var session = urlParams.get("session");
	
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&restoring&step=" + restoreStep + "&session=" + session;
  
  window.location.href = ref;
}
function toPreparing() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdPreparing = document.getElementById("cmdPreparing");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=preparing&item="+ item + "&session=" + session; 
  
  cmdPreparing.href = ref;
}
function toPrepared() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdPrepared = document.getElementById("cmdPrepared");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=prepared&item=" + item + "&session=" + session; 
  
  cmdPrepared.href = ref;
}
function toBaking() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdBaking = document.getElementById("cmdBaking");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=baking&item="+ item + "&session=" + session; 
  
  cmdBaking.href = ref;
}
function toBaked() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdBaked = document.getElementById("cmdBaked");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=baked&item="+ item + "&session=" + session; 
  
  cmdBaked.href = ref;
}
function toFinalized() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdFinalized = document.getElementById("cmdFinalized");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=finalized&item="+ item + "&session=" + session; 
  
  cmdFinalized.href = ref;
}
function toBegin() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdBegin = document.getElementById("cmdBegin");
  var ref = "application.cgi?station=" + station + "&step=none&session=" + session; 
  
  cmdBegin.href = ref;
}
function toContinue() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order"); 
  var item = document.getElementById("restoreItemList").value;
  var step = urlParams.get("step");  
  var session = urlParams.get("session");
    
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=" + step + "&item="+ item  + "&session=" + session; 
  
  window.location.href = ref;
}

function toCooking() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdCooking = document.getElementById("cmdCooking");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=cooking&item=" + item + "&session=" + session; 
  
  cmdCooking.href = ref;
}
function toCooked() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var station = urlParams.get("station");
  var orderSelected = urlParams.get("order");  
  var item = urlParams.get("item");  
  var session = urlParams.get("session");
    
  var cmdCooked = document.getElementById("cmdCooked");
  var ref = "application.cgi?station=" + station + "&order=" + orderSelected + "&step=cooked&item="+ item + "&session=" + session; 
  
  cmdCooked.href = ref;
}
function toOvenFinalized(order,item) 
{
	var cmdOvenFinalized = document.getElementById("cmdOvenFinalized");
    const urlParams = new URLSearchParams(window.location.search);
    var session = urlParams.get("session");
	
    var ref = "application.cgi?station=oven&order=" + order + "&step=finalized&item="+ item + "&session=" + session; 
    
    cmdOvenFinalized.href = ref;
}

function toHome() 
{  
  const urlParams = new URLSearchParams(window.location.search);
  var session = urlParams.get("session");
  var ref = "application.cgi?session=" + session;
  
  window.location.href = ref;
}
