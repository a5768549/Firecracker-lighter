function updateStatus(id,status)
{
    let statusText = "";
    console.log(id);
    (status == "1") ? statusText = "已點燃" : statusText = "未點燃";
    
    let ContentText = document.createTextNode("目前狀態：" + statusText);
    if(id == "1")
    {
        console.log("test");
        let status1 = document.getElementById("status1");
        status1.appendChild(ContentText);
    }

    if(id == "2")
    {
        let status2 = document.getElementById("status2");
        status2.appendChild(ContentText);
    }
    
}

function updateTime(id,time)
{
    if(id == "1")
    {
        document.getElementById("time1").value = time;
    }

    if(id == "2")
    {
        console.log(time);
        document.getElementById("time2").value = time;
    }

}

function timeset(device)
{
    var timeValue = ""
    if(device == 1)
    {
        timeValue = document.getElementById("time1").value;
    }
    else if(device == 2)
    {
        timeValue = document.getElementById("time2").value;
    }

    var data = {'timeValue': timeValue , 'ID' : device};

    fetch('../api/timeset-api.php', {
    method: 'POST',
    body: JSON.stringify(data),
    headers: new Headers({
        'Content-Type': 'application/json'
    })
    }).then(res => res.json())

    window.location.reload();
}

function timecancel(device)
{
    var time = "0000-00-00 00:00:00";

    var data = {'timeValue': time , 'ID' : device};

    fetch('../api/timeset-api.php', {
    method: 'POST',
    body: JSON.stringify(data),
    headers: new Headers({
        'Content-Type': 'application/json'
    })
    }).then(res => res.json())

    window.location.reload();
}

function burn(device)
{
    var time = "2000-01-01 00:00:00";

    var data = {'timeValue': time , 'ID' : device};

    fetch('../api/timeset-api.php', {
    method: 'POST',
    body: JSON.stringify(data),
    headers: new Headers({
        'Content-Type': 'application/json'
    })
    }).then(res => res.json())

    window.location.reload();
}

function homePageInit() 
{
    fetch('../api/index-api.php')
    .then(res => 
    {
        return res.json();
    })
    .then(result => 
    {
        result.result.forEach(element => {
            console.log(element);
            updateStatus(element['ID'],element['status']);
            updateTime(element['ID'],element['custom_date']);

        });
    })

    var timeset1 = document.getElementById("timeset1");
    var timeset2 = document.getElementById("timeset2");
    var timecancel1 = document.getElementById("timecancel1");
    var timecancel2 = document.getElementById("timecancel2");
    var burn1 = document.getElementById("burn1");
    var burn2 = document.getElementById("burn2");

    timeset1.onclick = function() {timeset('1')};
    timeset2.onclick = function() {timeset('2')};
    timecancel1.onclick = function() {timecancel('1')};
    timecancel2.onclick = function() {timecancel('2')};
    burn1.onclick = function() {burn('1')};
    burn2.onclick = function() {burn('2')};
}

