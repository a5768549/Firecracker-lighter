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
        //status1.appendChild(ContentText);
    }

    if(id == "2")
    {
        console.log(time);
        document.getElementById("time2").value = time;
        //status2.appendChild(ContentText);
    }

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
}