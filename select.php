<?php

$host = "localhost";
$user = "root";
$pass = "";
$db   = "DHT_db";

$conn = mysqli_connect($host, $user, $pass, $db);

if (!$conn) {
    die("Database connection failed");
}

$sel = mysqli_query($conn, "SELECT * FROM dht_data");

if(mysqli_num_rows($sel) > 0){
?>
<table border="1">
    <tr>
        <th>ID</th>
        <th>temperature</th>
        <th>humidity</th>
        <th>TIMESTAMP</th>
    </tr>

<?php
while($raws = mysqli_fetch_array($sel)){
?>
<tr>
    <td><?php echo $raws['id']; ?></td>
    <td><?php echo $raws['tempereture']; ?></td>
     <td><?php echo $raws['humidity']; ?></td>
    <td><?php echo $raws['timestamp']; ?></td>
</tr>
<?php } ?>

</table>
<?php
}
else{
    echo "no data available in database";
}
?>