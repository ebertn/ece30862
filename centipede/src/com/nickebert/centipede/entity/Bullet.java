package com.nickebert.centipede.entity;

import com.nickebert.centipede.Window;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.states.PlayState;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;
import com.sun.tools.javac.Main;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.applet.Applet;
import java.applet.AudioClip;
import java.awt.*;
import java.io.File;

public class Bullet extends Entity {

    private final float bullet_speed = 15f;
    private final int width = 2;
    private final int height = 20;

    public Bullet(Sprite sprite, Vector2f pos) {
        super(sprite, null);

        this.pos = pos;
        this.setMaxSpeed(bullet_speed);

        this.dy = -bullet_speed; // Move up
        this.dx = 0;

        this.hitBounds = new Collision(pos, width, height);

        playSound();
    }

    public Bullet(Sprite sprite, int x, int y){
        this(sprite, new Vector2f(x, y));
    }

    // Update is handled by Entity class

    @Override
    public void bulletHit() {}

    @Override
    public void render(Graphics2D g) {
        g.setColor(new Color(164,0, 255));
        g.fillRect((int) this.pos.x, (int) this.pos.y, width, height);
    }

    public boolean removable(){
        return this.pos.x > com.nickebert.centipede.Window.game_width || this.pos.x < 0
                || this.pos.y > Window.game_height || this.pos.y < 0;
    }

    public static synchronized void playSound() {
        new Thread(new Runnable() {
            // The wrapper thread is unnecessary, unless it blocks on the
            // Clip finishing; see comments.
            public void run() {
                File wavFile = PlayState.bulletSound;
                try {
                    AudioClip sound = Applet.newAudioClip(wavFile.toURL());
                    sound.play();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
