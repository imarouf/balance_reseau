<!DOCTYPE html>
<html><body>
<?php
 
$servername = 'localhost';
 
// REPLACE with your Database name
$dbname = 'id18229280_scaledata';
// REPLACE with Database user
$username = 'id18229280_ilyes84000';
// REPLACE with Database user password
$password = '0123456789aB!';
 
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
 
$sql = "SELECT * FROM sensordata ORDER BY recnum DESC";
 
echo '<table cellspacing="5" cellpadding="5">
      <tr>
        <td>renum</td>
        <td>lecture</td>
        <td>lecture_avg</td>
        <td>date</td>
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_recnum = $row["recnum"];
        $row_lecture = $row["lecture"];
        $row_lecture_avg = $row["lecture_avg"];
        $row_date = $row["date"];
        
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
     
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
     
        echo '<tr>
                <td>' . $row_recnum . '</td>
                <td>' . $row_lecture . '</td>
                <td>' . $row_lecture_avg . '</td>
                <td>' . $row_date . '</td>
              </tr>';
    }
    $result->free();
}
 
$conn->close();
?>
</table>
</body>
</html>
