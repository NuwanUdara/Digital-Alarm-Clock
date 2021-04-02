#include <LiquidCrystal.h>
#include <string.h>
#include <stdlib.h>
#define LCD_ROWS 4
#define LCD_COLS 20

char lcd_buf[LCD_ROWS][LCD_COLS];
char lcd_buf_old[LCD_ROWS][LCD_COLS];
int  lcd_buf_x, lcd_buf_y;

void buf_locate(int, int);
void buf_char(char);
void buf_clear(void);
void lcd_refresh(void);
void buf_str(char *);
void buf_str_XY(int, int, char *);
void buf_int(int);
void buf_clear_menu(void);

typedef struct menu_t{
  const char * name;
  menu_t * next;
  menu_t * prev;
  menu_t * child;
  menu_t * parent;
  void (*menu_function)(void);
};

void key_next_press(void);
void key_prev_press(void);
void key_enter_press(void);
void key_back_press(void);

void (*key_next_func)(void) = &menu_next;
void (*key_prev_func)(void) = &menu_prev;
void (*key_enter_func)(void)= &menu_enter;
void (*key_back_func)(void) = &menu_back;

void Change(void);void Show(void);
void Change(void);void Show(void);
void Change(void);
void Listen(void);
void settings(void);

int menu_index=0;
int lcd_row_pos=0;
int lcd_row_pos_level_1=0, lcd_row_pos_level_2=0;

menu_t menu1;
  menu_t sub_menu1_1;
  menu_t sub_menu1_2;
menu_t menu2;
  menu_t sub_menu2_1; 
  menu_t sub_menu2_2;
menu_t menu3;
  menu_t sub_menu3_1; 
menu_t menu4;
  menu_t sub_menu4_1; 
    menu_t sub_menu4_1_1;
    menu_t sub_menu4_1_2;
    menu_t sub_menu4_1_3;
    menu_t sub_menu4_1_4; 
  menu_t sub_menu4_2;
menu_t menu5;
menu_t *currentPointer=&menu1;

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);
void setup() {
// definition of menu's items: (*name, *next, *prev, *child, *parent, (*menu_function)) 
// I used some (*menu_function) like (change,show) others put null if we want to put fuction then it okay
menu1={ "TIME", &menu2, &menu5, &sub_menu1_1, NULL, NULL };
  sub_menu1_1={ "Change", &sub_menu1_2, &sub_menu1_2,NULL, &menu1, Change };
  sub_menu1_2= { "Show", NULL, &sub_menu1_1, NULL, &menu1,Show};
menu2={ "DATE", &menu3, &menu1, &sub_menu2_1, NULL, NULL };
  sub_menu2_1={ "Change", &sub_menu2_2, &sub_menu2_2, NULL, &menu2, Change};
  sub_menu2_2={ "Show", NULL, &sub_menu2_1, NULL, &menu2, Show};
menu3={ "COLOR", &menu4, &menu2, &sub_menu3_1, NULL,NULL};
  sub_menu3_1={ "Change", NULL,&sub_menu3_1, NULL, &menu3,NULL};
menu4={ "RINGING_TONE", &menu5, &menu3, &sub_menu4_1, NULL, NULL };
  sub_menu4_1={ "Change", &sub_menu4_2, &sub_menu4_2, &sub_menu4_1_1, &menu4, NULL };
    sub_menu4_1_1={ "Game_of_thrones",&sub_menu4_1_2, &sub_menu4_1_4, NULL, &sub_menu4_1, NULL };
    sub_menu4_1_2={ "Pirates_of_the_caribean",&sub_menu4_1_3, &sub_menu4_1_1, NULL, &sub_menu4_1, NULL };
    sub_menu4_1_3={ "eauty_and_beast",&sub_menu4_1_4, &sub_menu4_1_2, NULL, &sub_menu4_1, NULL };
    sub_menu4_1_4={ "Dark",NULL, &sub_menu4_1_1, NULL, &sub_menu4_1, NULL};
  sub_menu4_2={ "Listen", NULL, &sub_menu4_1, NULL, &menu4, NULL};
menu5={ "SETTINGS", NULL, &menu4, NULL, NULL, settings };

  lcd.begin(20, 4);
  lcd.setCursor(0,0);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  menu_refresh();
}

void loop() {
  key_next_press();
  delay(50);
  key_prev_press();
  delay(50);
  key_enter_press();
  delay(50);
  key_back_press();
  delay(50);
  lcd_refresh();
}

void menu_refresh(void) {
  menu_t *temp=NULL;
  int i;
  int center;
  for(int i=0;i<LCD_COLS;i++){
    lcd_buf[0][i]='-';
  }
  if ((currentPointer->parent)!=NULL) {
    temp = (currentPointer->parent)->child;
    center = ( LCD_COLS - (strlen((temp->parent)->name)) )>>1;
    buf_locate(center-1,0);
    buf_char(' ');
    buf_str((temp->parent)->name);
    buf_char(' ');
  }
  else {
    temp = &menu1;
    center = (LCD_COLS - 4)>>1;
    buf_str_XY(center-1,0," MENU ");
  }
  for (i = 0; i != menu_index - lcd_row_pos; i++) {
    temp = temp->next;
  }
  buf_clear_menu();
  for (i = 1; i < LCD_ROWS; i++) {
    buf_locate(0, i);
    if (temp == currentPointer) 
      buf_char(62);
    else 
      buf_char(' ');
    buf_locate(2, i);
    buf_str(temp->name);
    temp = temp->next;
    if (!temp) 
      break;
  }
  // lcd_refresh();
}

int menu_get_index(menu_t *q) {
  menu_t *temp;
  int i = 0;
  if (q->parent) temp = (q->parent)->child;
  else temp = &menu1;
  while (temp != q) {
    temp = temp->next;
    i++;
  }
  return i;
}

int menu_get_level(menu_t *q) {
  menu_t *temp = q;
  int i = 0;
  if (!q->parent) return 0;
  while (temp->parent != NULL) {
    temp = temp->parent;
    i++;
  }
  return i;
}

void menu_next(void) {
  if (currentPointer->next){
    currentPointer = currentPointer->next;
    menu_index++;
    if (++lcd_row_pos > LCD_ROWS - 2) 
      lcd_row_pos = LCD_ROWS - 2;
  }
  else{
    menu_index = 0;
    lcd_row_pos = 0;
    if (currentPointer->parent) currentPointer = (currentPointer->parent)->child;
    else currentPointer = &menu1;
  }
  menu_refresh();
}

void menu_prev(void) {
  currentPointer = currentPointer->prev;
  if (menu_index){
    menu_index--;
    if (lcd_row_pos > 0) lcd_row_pos--;
  }
  else{
    menu_index = menu_get_index(currentPointer);
    if (menu_index >= LCD_ROWS - 2) lcd_row_pos = LCD_ROWS - 2;
    else lcd_row_pos = menu_index;
  }
  menu_refresh();
}

void menu_enter(void) {
  if (currentPointer->menu_function)
    currentPointer->menu_function();
  if (currentPointer->child){
    switch (menu_get_level(currentPointer)) {
      case 0:
        lcd_row_pos_level_1 = lcd_row_pos;
        break;
      case 1:
        lcd_row_pos_level_2 = lcd_row_pos;
        break;
    }
    // switch case can be replaced:
    // lcd_row_pos_level[ menu_get_level(currentPointer) ] = lcd_row_pos;
    menu_index = 0;
    lcd_row_pos = 0;
    currentPointer = currentPointer->child;
    menu_refresh();
  }
}

void menu_back(void) {
  if (currentPointer->parent) {
    switch (menu_get_level(currentPointer)) {
      case 1:
        lcd_row_pos = lcd_row_pos_level_1;
        break;
      case 2:
        lcd_row_pos = lcd_row_pos_level_2;
        break;
      }
    currentPointer = currentPointer->parent;
    menu_index = menu_get_index(currentPointer);
    menu_refresh();
  }
}

void buf_locate(int x, int y){
  lcd_buf_x = x;
  lcd_buf_y = y;
}

void buf_char(char c){
if (lcd_buf_x < LCD_COLS && lcd_buf_y < LCD_ROWS)
  {
    lcd_buf[lcd_buf_y][lcd_buf_x] = c;
    lcd_buf_x++;
    if (lcd_buf_x == LCD_COLS) {
      lcd_buf_x = 0;
      lcd_buf_y++;
      if (lcd_buf_y == LCD_ROWS)
        lcd_buf_y = 0;
    }
  }
}

void buf_clear(void){
  for(int y=0; y<LCD_ROWS; y++){
    for(int x=0; x<LCD_COLS; x++){
      lcd_buf[y][x]=' ';
    }
  }
  lcd_buf_x=0; lcd_buf_y=0;
}

void buf_clear_menu(void){
  for(int y=1; y<LCD_ROWS; y++){
    for(int x=0; x<LCD_COLS; x++){
      lcd_buf[y][x]=' ';
    }
  }
  lcd_buf_x=0; lcd_buf_y=0;
}

void lcd_refresh(void){
  static int locate_flag = 0; // informs when lcd cursor position have to be changed
  for(int y=0; y<LCD_ROWS; y++){
     lcd.setCursor( 0, y );
    for(int x=0; x<LCD_COLS; x++){
      if( lcd_buf[y][x] != lcd_buf_old[y][x] ){
        if( !locate_flag )
           lcd.setCursor( x, y );
        lcd.print( lcd_buf[y][x] );
        lcd_buf_old[y][x] = lcd_buf[y][x];
        locate_flag = 1;
      }
      else
        locate_flag = 0;
    }
  }
}
void buf_str(char *text){
  while(*text)
    buf_char(*text++);
}
void buf_str_XY(int x, int y, char *text){
  buf_locate(x,y);
  while(*text)
    buf_char(*text++);
}
void buf_int(int value){
  char string[5];
  itoa(value, string, 10);
  buf_str(string);
}
void key_next_press(void){
  int key_next_lock=0;
  if( !key_next_lock && (digitalRead(2))){
      key_next_lock=1;
    if(key_next_func) 
      (*key_next_func)();
  } 
  else if(key_next_lock && !(digitalRead(2))) 
      key_next_lock++;
}

void key_prev_press(void){
  int key_prev_lock=0;
  if( !key_prev_lock && (digitalRead(3))){
      key_prev_lock=1;
    if(key_prev_func) 
      (*key_prev_func)();
  } 
  else if( key_prev_lock && !(digitalRead(3))) 
       key_prev_lock++;
}

void key_enter_press(void){
  int key_enter_lock=0;
  if( !key_enter_lock && (digitalRead(1))){
    key_enter_lock=1;
  if(key_enter_func) 
    (*key_enter_func)();
  } 
  else if( key_enter_lock && !(digitalRead(1))) 
      key_enter_lock++;
}
void key_back_press(void){
  int key_back_lock=0;
  if( !key_back_lock && (digitalRead(4))){
       key_back_lock=1;
    if(key_back_func) 
      (*key_back_func)();
  } 
  else if( key_back_lock && !(digitalRead(4)))
      key_back_lock++;
}
void change(void){
  buf_clear_menu();
}
void Show(void){}
void Change(void){}
void settings(void){}
