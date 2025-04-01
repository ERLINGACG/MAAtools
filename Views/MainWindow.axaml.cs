using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.Animation;
using Avalonia.Animation.Easings;
using Avalonia.Styling;
using Avalonia.Layout;
using Avalonia.Interactivity;
using System.Security.Cryptography.X509Certificates;
using MAAtools.ViewModels;
using System.ComponentModel;
namespace MAAtools.Views;




public partial class MainWindow : Window
{

    public  void SetSytle_Sidebar(){  //设置侧边栏样式
        Sidebar.Background =new SolidColorBrush(Color.Parse("#222254"));;
        Sidebar.Width = 40;
        Sidebar.Height = Height+20;
        Sidebar.HorizontalAlignment = Avalonia.Layout.HorizontalAlignment.Left;
           var shadow = new DropShadowEffect
            {
                BlurRadius = 10.0f,
                // 使用 8 位十六进制包含透明度
                Color = Color.Parse("#CC000000"), 
            };


        // 应用阴影效果
        SidebarBorder.Effect = shadow;
        void Set_Buttom_Style(double height, double width){
            Sidebar_Buttom1.Height = height;
            Sidebar_Buttom1.Width = width;
            Sidebar_Buttom2.Height = height;
            Sidebar_Buttom2.Width = width;
            Sidebar_Buttom3.Height = height;
            Sidebar_Buttom3.Width = width;
            Settings.Height = height;
            Settings.Width = width;

            
        }
        Sidebar_Buttom1.Content = "";
        Sidebar_Buttom2.Content = "";
        Sidebar_Buttom3.Content = "";
        Settings.Content = "";


        Set_Buttom_Style(50,40);
        Sidebar.Transitions =
        [
                new DoubleTransition
                {
                    Property = Layoutable.WidthProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }
        ];
        Sidebar_Buttom1.Transitions = [
            new DoubleTransition
                {
                    Property = Layoutable.WidthProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }

        ];
        Sidebar_Buttom2.Transitions = [
            new DoubleTransition
                {
                    Property = Layoutable.WidthProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }

        ];
        Sidebar_Buttom3.Transitions = [
            new DoubleTransition
                {
                    Property = Layoutable.WidthProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }

        ];
        Settings.Transitions = [
            new DoubleTransition
                {
                    Property = Layoutable.WidthProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }

        ];
        CurrentPage.Margin = new Thickness(-40, 70, 0, 0);
        SidebarBorder.PointerEntered += (s, e) =>{
            Sidebar.Width = 200;
            Sidebar_Buttom1.Content = "生息演算小助手";
            Sidebar_Buttom2.Content = "星穹铁道小助手";
            Sidebar_Buttom3.Content = "敬请期待";
            Settings.Content = "设置";

            // Margin 动画平移
            CurrentPage.Transitions = new Transitions
            {
                new ThicknessTransition
                {
                    Property = MarginProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }
            };

            CurrentPage.Margin = new Thickness(200, 70, 0, 0); // 子页面向右动态平移
            Set_Buttom_Style(50, 200);
        };
        
        SidebarBorder.PointerExited += (s, e) =>
        {
            Sidebar.Width = 40;
            Sidebar_Buttom1.Content = "";
            Sidebar_Buttom2.Content = "";
            Sidebar_Buttom3.Content = "";
            Settings.Content = "";

            // Margin 动画复原
            CurrentPage.Transitions = new Transitions
            {
                new ThicknessTransition
                {
                    Property = MarginProperty,
                    Duration = TimeSpan.FromMilliseconds(400),
                    Easing = new CubicEaseOut()
                }
            };

            CurrentPage.Margin = new Thickness(-40, 70, 0, 0); // 子页面向左动态平移
            Set_Buttom_Style(50, 40);
        };
}


     private readonly Page1 _page1 = new Page1(); // 声明一个Page1实例
     private readonly Page2 _page2 = new Page2(); // 声明一个Page2实例
     private readonly Page3 _page3 = new Page3(); // 声明一个Page3实例
     private readonly Settings _setting = new Settings(); // 声明一个Settings实例
    public MainWindow()
    {   
        
        InitializeComponent();
        SetSytle_Sidebar();
        CurrentPage.Content = _page1;
        Closing += MainWindow_Closing;
        
        // this.Opened += OnMainWindowOpened;


    }
    private void ShowPage1(object sender, RoutedEventArgs e){
        CurrentPage.Content = _page1;
    }
    private void ShowPage2(object sender, RoutedEventArgs e){
        CurrentPage.Content = _page2;
    }
    private void ShowPage3(object sender, RoutedEventArgs e){
        CurrentPage.Content = _page3;
    }
    private void ShowSetting(object sender, RoutedEventArgs e){
        CurrentPage.Content = _setting;
    }

     private async void OnMainWindowOpened(object? sender, EventArgs e)
            {
                var noticeWindow = new NoticeWindow();
                await noticeWindow.ShowDialog(this);
            }

     private void MainWindow_Closing(object sender, CancelEventArgs e)
    {

        if (DataContext is Page1ViewModel vm)
        {   
            Console.WriteLine("关闭成功");
            vm.Shutdown();
            
        }
    }
}