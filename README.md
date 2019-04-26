# CallSystemInterception
Small projetc to test intercepting call systems

# Sources

http://samanbarghi.com/blog/2014/09/05/how-to-wrap-a-system-call-libc-function-in-linux/

# Ideas
- Statistics on system call
- Intercept tcp or udp call
- Intercept and edit email send
    - Add person in carbon copy
- Open another file random when opening file with blocknote

# Rapport
- Add wrong TCP Packet to hide RCP_TO
- Seperate RCP_TO byte by byte

To compile:
- pandoc --filter pandoc-citeproc rapport.md --standalone --to latex --latex-engine xelatex --output rapport.pdf