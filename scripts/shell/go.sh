#!/usr/bin/expect --

puts "tt.sh..."
if { [llength $argv] < 4} { 

	puts "usage: $argv0 ip user passwd task_id"  
	exit 1
}
set ip [lindex $argv 0]
set user [lindex $argv 1]
set passwd [lindex $argv 2]
set task_id [lindex $argv 3]

set success 0

set maxRetry 2
for {set retryNum 0} {$retryNum<$maxRetry} {incr retryNum} {

puts "try $retryNum"
spawn ssh -q $user@$ip#36000 

set timeout 600
expect { 
	"password:" {    	
		send "$passwd\r"	
        set timeout 600
        expect {
        "#" {
            send "source /t-borg/go_taskdir.sh $task_id\r"
            interact
            set success 1
            break
        }
        timeout {continue}
        }
    }

	"yes/no)?" {
		send "yes\r"
		expect "password:" {
			send "$passwd\r"
			set timeout 600
			expect { 
                "#" {
                    send "source /t-borg/go_taskdir.sh $task_id\r"
                    interact
                    set success 1
                    break
                }
            timeout {continue}
            }
        }
    }
}
}
