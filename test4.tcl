
# —————-ESTABLISHING COMMUNICATION ————-#

#——–CLIENT1 TO ENDSERVER ————-#

set tcp0 [new Agent/TCP]
$tcp0 set maxcwnd_ 16
$tcp0 set fid_ 4
$ns attach-agent $Client1 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $Endserver1 $sink0

$ns connect $tcp0 $sink0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

$ns add-agent-trace $tcp0 tcp
$tcp0 tracevar cwnd_

$ns at 0.5 "$ftp0 start"
$ns at 28.5 "$ftp0 stop"

# —————-CLIENT2 TO ENDSERVER1 ————-#
set tcp1 [new Agent/TCP]
$tcp1 set fid_ 2
$tcp1 set maxcwnd_ 16
$ns attach-agent $Client2 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $Endserver1 $sink1

$ns connect $tcp1 $sink1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

$ns add-agent-trace $tcp1 tcp1
$tcp1 tracevar cwnd_

$ns at 0.58 "$ftp1 start"
$ns at 28.5 "$ftp1 stop"

# —————- CLIENT3 TO ENDSERVER ————-#
set tcp2 [new Agent/TCP]
$tcp2 set fid_ 0
$tcp2 set maxcwnd_ 16
$tcp2 set packetsize_ 100
$ns attach-agent $Client3 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $Endserver1 $sink2
$ns connect $tcp2 $sink2

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ns add-agent-trace $tcp2 tcp2
$tcp2 tracevar cwnd_

$ns at 0.65 "$ftp2 start"
$ns at 28.5 "$ftp2 stop"

#——————–CLIENT4 TO ENDSERVER—————-#

set tcp3 [new Agent/TCP]
$tcp3 set fid_ 3
$tcp3 set maxcwnd_ 16
$tcp2 set packetsize_ 100
$ns attach-agent $Client4 $tcp3

set sink3 [new Agent/TCPSink]
$ns attach-agent $Endserver1 $sink3

$ns connect $tcp3 $sink3

set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3

$ns add-agent-trace $tcp3 tcp3
$tcp3 tracevar cwnd_

$ns at 0.60 "$ftp3 start"
$ns at 28.5 "$ftp3 stop"

#———— Link Failure ————–#

$ns rtmodel-at 2.880511 down $Router3 $Router4

#———— Link Failure Recovery ————–#

$ns rtmodel-at 5.880511 up $Router3 $Router4
