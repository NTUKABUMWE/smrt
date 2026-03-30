<?php
$host="localhost";
$username = "root"; 
$password = "";     
$dbname = "iot_data";
$con= mysqli_connect("localhost","root","","iot_data");
$select=mysqli_query($con,"select * from sensor_data");
if(mysqli_num_rows($select)>0)
{
    ?>
    <p><SENSOR DASHBOARD</u></p>
    <table border="1">
        <th><tr><td>id</td><td>temperature</td><td>humidity</td><td>created_at</td></tr></th>
<?php
while($data=mysqli_fetch_array($select)){
?>
<tr><td><?php echo $data["id"];?></td><td><?php echo $data["temperature"];?></td><td><?php echo $data["humidity"];?></td><td><?php echo $data["created_at"];?></td></tr>
 <?php

}
?>
</table>
<?php
}

