; 브라우저에서 이미지 파일에 마우스 커서를 올린 후 Alt+S 키 사용
; 저장폴더를 변경하기 위해서는 처음 1번은 수동으로 저장해야 함

; ! : Alt Key
; + : Shift Key
; ^ ; Control Key
; # : Window Key

;!s::msgbox, TEST

!s::
MouseClick right    ; 우측마우스 클릭

Sleep, 100          ; 우측 메뉴 활성화
Send {Down 2}       ; '이미지를 다른이름으로 저장' 선택
Send {Enter}        ; 실행

Sleep, 300          ; '다른이름으로 저장'창 활성화
Send !{S}           ; 저장 단축키
