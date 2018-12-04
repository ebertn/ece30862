package com.nickebert.centipede.entity;

import com.nickebert.centipede.Window;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;

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
}
