package com.nickebert.centipede.graphics;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class Sprite {

    private BufferedImage SPRITESHEET = null;
    private BufferedImage[][] spriteArray;
    private final int TILE_SIZE = 32;
    public int width;
    public int height;
    private int wSprite;
    private int hSprite;

    public Sprite(String file){
//        width = TILE_SIZE;
//        height = TILE_SIZE;
//
//        System.out.println("Loading " + file + "...");
//        SPRITESHEET = loadSprite(file);
//
//        wSprite = SPRITESHEET.getWidth() / width;
//        hSprite = SPRITESHEET.getHeight() / height;
//        loadSpriteArray();
    }

    public Sprite(String file, int w, int h){
        this.width = w;
        this.height = h;

        System.out.println("Loading " + file + "...");
        SPRITESHEET = loadSprite(file);

        wSprite = SPRITESHEET.getWidth() / width;
        hSprite = SPRITESHEET.getHeight() / height;
        loadSpriteArray();
    }

    public void setSize(int width, int height){
        setWidth(width);
        setHeight(height);
    }

    public void setWidth(int w){
        width = w;
        wSprite = SPRITESHEET.getWidth();
    }

    public void setHeight(int h){
        height = h;
        hSprite = SPRITESHEET.getHeight();
    }

    public int getWidth(){ return width; }
    public int getHeight(){ return height; }

    private BufferedImage loadSprite(String file){
        BufferedImage sprite = null;
        try{
            sprite = ImageIO.read(getClass().getClassLoader().getResourceAsStream(file));
        } catch(Exception e){
            System.out.println("ERROR: could not load file: " + file);
        }

        return sprite;
    }

    public void loadSpriteArray(){
        spriteArray = new BufferedImage[wSprite][hSprite];

        for(int x = 0; x < wSprite; x++){
            for(int y = 0; y < hSprite; y++){
                spriteArray[x][y] = getSprite(x, y);
            }
        }
    }

    public BufferedImage getSpriteSheet() {return SPRITESHEET;}

    public BufferedImage getSprite(int x, int y){
        return SPRITESHEET.getSubimage(x * width, y * height, width, height);
    }

    public BufferedImage[] getSpriteArray(int i){
        return spriteArray[i];
    }

    public BufferedImage[][] getSpriteArray2(int i){
        return spriteArray;
    }
}
