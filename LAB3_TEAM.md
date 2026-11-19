# Lab 3 – Page Table: quy trình làm việc nhóm

Branch gốc: `lab3-pgtbl` (code khởi đầu từ MIT xv6-labs-2023, branch `pgtbl`).
Không commit thẳng vào `lab3-pgtbl`: mỗi người làm trên branch riêng rồi mở Pull Request vào `lab3-pgtbl`.

| Phần | Branch | Người làm |
|---|---|---|
| 4.1 Tăng tốc syscall (ugetpid / USYSCALL) | `feat/lab3-p1-ugetpid` | ... |
| 4.2 In bảng trang (vmprint) | `feat/lab3-p2-vmprint` | ... |
| 4.3 pgaccess | `feat/lab3-p3-pgaccess` | ... |

## Bắt đầu
```bash
git fetch origin
git checkout feat/lab3-pX-...        # branch phần của bạn
make qemu                            # chạy thử
./grade-lab-pgtbl                    # hoặc: make grade
```

## Lưu ý
- Code gốc ĐÃ CÓ sẵn: `USYSCALL` + `struct usyscall` (kernel/memlayout.h), `ugetpid()` (user/ulib.c),
  khung `sys_pgaccess` (kernel/sysproc.c), syscall number và stub user. Không định nghĩa lại.
- Phần 2 cần giải thích các trang lá; phần 1 cần trả lời câu hỏi thêm. Ghi vào `answers-pgtbl.txt`.
- Trước khi mở PR: `git fetch origin && git rebase origin/lab3-pgtbl`, chạy `make grade` để chắc chắn không làm hỏng phần khác.
- Không commit file build (`*.o`, `*.d`, `kernel/kernel`, `fs.img`...) và các file PDF đề bài.

## Nộp bài (leader)
```bash
git diff mit/pgtbl lab3-pgtbl > ID1_ID2_ID3.patch   # hoặc diff so với commit gốc 66e11db
make clean   # rồi nén source
```
