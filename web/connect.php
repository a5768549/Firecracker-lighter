<?php

/** @var string mysql 主機 */
$mysql_conn_host = "localhost";

/** @var string mysql DB名稱 */
$mysql_conn_dbname = "firecracker";

/** @var string mysql 帳號 */
$mysql_conn_account = "root";

/** @var string mysql 密碼 */
$mysql_conn_password = "Aa970236";

/** @var PDO mysql 連線 */
$mysql_conn = new PDO(
    "mysql:host=$mysql_conn_hostname;dbname=$mysql_conn_dbname;charset=utf8",
    $mysql_conn_account,
    $mysql_conn_password
);