function createFallingEmoji() {
      const emojiList = ["💖", "✨", "💎", "🌸"];
      const emoji = document.createElement("div");
      emoji.classList.add("falling");
      emoji.textContent = emojiList[Math.floor(Math.random() * emojiList.length)];

      emoji.style.left = Math.random() * window.innerWidth + "px";
      emoji.style.fontSize = (20 + Math.random() * 25) + "px";
      const duration = 3 + Math.random() * 5;
      emoji.style.animationDuration = duration + "s";

      document.body.appendChild(emoji);

      setTimeout(() => {
        emoji.remove();
      }, duration * 1000);
    }
    setInterval(createFallingEmoji, 300);