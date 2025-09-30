


---

# 🛠 MyKernel — Mini Kernel Bare-Metal para AArch64

## 📅 Data
30 de Setembro de 2025

## 📝 Descrição
**MyKernel** é um projeto experimental de kernel bare-metal desenvolvido para arquitetura **AArch64**, rodando no **QEMU**.  
Ele inclui um shell interativo básico, suporte a comandos, edição de linha, histórico e estrutura modular para expansão futura.

Este projeto foi desenvolvido usando **Termux/proot-distro** em Android e Debian, com suporte completo para UART e console via drivers personalizados.

---

## ⚙ Estrutura do Projeto

mykernel/ ├── arch/              # Código de inicialização ├── drivers/           # Drivers de console, UART, buffer e strings ├── include/           # Headers ├── kernel/            # Lógica principal do kernel e shell ├── linker.ld          # Script de linker ├── Makefile           # Script de compilação ├── serial.out         # Saída do QEMU ├── kernel.img         # Imagem do kernel ├── kernel.elf         # Executável do kernel └── ...

---

## 🚀 Funcionalidades
- Inicialização bare-metal com `kernel_main`
- Drivers UART e Console
- Shell interativo com:
  - Prompt customizado
  - Comandos: `help`, `clear`, `echo`, `ls`, `cat`, `edit`, `reboot`
  - Histórico de comandos (setas ↑/↓)
  - Edição de linha (backspace, setas ←/→)
- Estrutura modular para expansão
- Compatível com QEMU em arquitetura ARM64

---

## 🛠 Build & Execução
No Debian/Termux, execute:
```bash
make
make run

O shell será carregado no QEMU:

Bem-vindo ao Shell++! >


---

📈 Progresso Atual

O kernel já está funcional, com shell interativo, histórico de comandos e edição de linha.
Pronto para expansões como:

Sistema de arquivos real

Comandos avançados

Multitarefa

Editor de texto completo

Reboot funcional via PSCI



---

📚 Próximos Passos

Melhorar saída interativa

Expandir shell com novos comandos

Criar sistema de arquivos básico

Implementar multitarefa



---

📂 Backup & Controle de Versão

Projeto disponível no GitHub: https://github.com/Sidneiba/shell

Faça backup localmente:

tar -czf mykernel_backup.tar.gz ~/mykernel


---

✨ Autor

Sidnei Batista
💻 Desenvolvedor de sistemas bare-metal e entusiasta de kernel
📧 Contato


---

📜 Licença

Este projeto está sob a licença MIT — sinta-se livre para estudar, modificar e distribuir.

---

Se quiser, eu posso agora gerar também uma **versão estilizada** desse README com emojis, tabelas, links bonitos e até badges do GitHub, para deixar seu repositório com aparência profissional e chamativa.  

Quer que eu faça isso?

