<?php
date_default_timezone_set("Asia/Taipei");
include('connect.php');
$data   =  json_decode(file_get_contents('php://input'),true);

$device = $data['device'];
$action = $data['action']; 
$value  = $data['value']; 


if(!isset($device) or !isset($action))
{
    http_response_code(400);
    exit('error');
}

switch($action)
{
    case 'status':
        if($value == 1)
        {
            $sql = "UPDATE `contorl` set `status` = 1 where `ID` = ?";
            $result =$con->prepare($sql);
            $result->execute(array($device));
        }
        else
        {
            $sql = "UPDATE `contorl` set `status` = 0 where `ID` = ?";
            $result =$con->prepare($sql);
            $result->execute(array($device));
        }
    break;

    case 'time':
        $sql = "SELECT * FROM `contorl` where `ID` = ?";
        $result =$con->prepare($sql);
        $result->execute(array($device));
        $result2 = $result->fetch(PDO::FETCH_ASSOC);
        echo $result2['scheduled_time'];
    break;
}

http_response_code(200);
exit();
