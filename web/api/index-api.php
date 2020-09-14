<?php
include("./shared.php");

/** @var PDOStatement 文章查詢敘述 */
$data_search_statement = $mysql_conn->prepare(
    "SELECT *,DATE_FORMAT(`scheduled_time`, '%Y-%m-%dT%H:%i') as custom_date
    FROM contorl"
);

$data_search_statement->execute();

/** @var array 文章 */
$data = $data_search_statement->fetchAll(PDO::FETCH_ASSOC);
http_response_code(200);
respond_json(["result" => $data]);