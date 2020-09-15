<?php
include("./shared.php");

$data   =  json_decode(file_get_contents('php://input'),true);

/** @var PDOStatement 文章查詢敘述 */
$data_search_statement = $mysql_conn->prepare(
    "UPDATE `contorl` 
    SET scheduled_time = ?
    WHERE ID = ?"
);

$data_search_statement->execute(array($data['timeValue'],$data['ID']));

http_response_code(200);