<?php

$host = "localhost";
$user = "root";
$pass = "";
$db   = "Motion_db";

$conn = mysqli_connect($host, $user, $pass, $db);

if (!$conn) {
    die("Database connection failed");
}

$sel = mysqli_query($conn, "SELECT * FROM Motion_data");

if(mysqli_num_rows($sel) > 0){
?>
<table border="1">
    <tr>
        <th>ID</th>
        <th>motion_detected</th>
        <th>TIMESTAMP</th>
    </tr>

<?php
while($raws = mysqli_fetch_array($sel)){
?>
<tr>
    <td><?php echo $raws['id']; ?></td>
    <td><?php echo $raws['motion_detected']; ?></td>
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