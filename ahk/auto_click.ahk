
; 특정 Window 모든 창을 찾아 Eneter Key를 입력

F5::
MsgBox 0, AutoHotKey, 자동 클릭 시작 (10분) !, 10
setTimer, go_wake, 600000

return

go_wake:

WinGet, id, List, 70.12
loop %id% {
	this_id := id%A_Index%
	WinActivate, ahk_id %this_id%
	sleep 1000
	Send {Enter}
}

return

F6::

setTimer, go_wake, off
MsgBox 0, AutoHotKey, 자동 클릭 중지 !, 10

return

