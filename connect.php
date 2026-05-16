<?php
$host="localhost";
$user="root";
$pass="";
$db="DHT_db";

$conn=mysqli_connect($host,$user,$pass,$db);

if ($conn){
    echo "connection successfull";
}
else{
    echo "connection failed"; 
}

$data=json_decode(file_get_contents("php://input"),true);

if ($data){

    $distance=$data["INtera"];

    $insert=mysqli_query($conn,"insert into DHT_data(temperature) values('$tempereture','$humidity')");

    if ($insert){
        echo "data inserted successfully";
    }

}
else{
    echo "no data recevied from esp32";
}

?>