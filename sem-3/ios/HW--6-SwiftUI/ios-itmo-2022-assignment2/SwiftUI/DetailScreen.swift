//
//  DetailScreen.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 29.12.2022.
//

import SwiftUI

struct DetailScreen: View {
    
    var object : Page
    @State private var presentShare = false
    weak var navigationController : UINavigationController?
    
    var body: some View {
        ScrollView(.vertical, showsIndicators: false, content: {
            LazyVStack(pinnedViews: [.sectionHeaders]) {
                Section(header:
                    ZStack {
                    Image(uiImage: object.image ?? UIImage(imageLiteralResourceName: "defaultImageFilm"))
                            .resizable()
                            .frame(width: UIScreen.main.bounds.width, height:  UIScreen.main.bounds.height*0.75)
                            .aspectRatio(contentMode: .fill)
                        
                        Rectangle()
                            .foregroundColor(.clear)
                            .background(LinearGradient(gradient: Gradient(colors: [.clear, .black]), startPoint: .top, endPoint: .bottom))
                            .edgesIgnoringSafeArea(.all)
                        
                        HStack{
                            Button{
                                navigationController?.popViewController(animated: true)
                                navigationController?.setNavigationBarHidden(false, animated: false)
                            }label: {
                                Image("backSwiftUI")
                            }
                            .offset(x: -UIScreen.main.bounds.width*0.36)
                            
                            Button{
                                self.presentShare = true
                            }label: {
                                Image("shareSwiftUI")
                            }.sheet(isPresented: $presentShare){
                                ActivityView()
                            }
                            .offset(x: UIScreen.main.bounds.width*0.36)
                        }.offset(y: -UIScreen.main.bounds.height*0.27)
                }
                            
                ){
                    VStack() {
                        Text(object.name)
                            .foregroundColor(.white)
                            .font(.system(size: 24))
                        Spacer().frame(height: 10)
                        Text(object.author)
                            .foregroundColor(.gray)
                            .font(.system(size: 16))
                        Spacer().frame(height: 22)
                        HStack{
                            Text("\(object.cnt)/5")
                                .foregroundColor(.white)
                                .font(.system(size: 30))
                            ForEach(0..<object.cnt, id: \.self){ _ in
                                Image("StarYellow")
                                    .resizable()
                                    .frame(width: 18, height: 18)
                            }
                            ForEach(object.cnt..<5, id: \.self){ _ in
                                Image("StarGray")
                                    .resizable()
                                    .frame(width: 18, height: 18)
                            }
                        }
                        Spacer().frame(height: UIScreen.main.bounds.height*0.14)
                        Text("Описание")
                            .foregroundColor(.white)
                            .font(.system(size: 24))
                        Spacer().frame(height: 12)
                        Text(object.description ?? "Добавьте описание в поле изменить, из таблицы с фильмами :)")
                            .foregroundColor(.white)
                            .font(.system(size: 16))
                    }
                    .padding(.top, 25)
                    .padding(.horizontal)
                    .background(Color.black)
                    .cornerRadius(20)
                    .offset(y: -35)
                }
            }
        })
        .edgesIgnoringSafeArea(.all)
        .background(Color.black)
        .navigationBarBackButtonHidden(true)
        .animation(.spring(response: 0.7, dampingFraction: 0.7, blendDuration: 0.7))
    }
}

struct DetailScreen_Previews: PreviewProvider {
    static var previews: some View {
        DetailScreen(object: Page(author: "I am", name: "New name", cnt: 3, imagePath: "", image: UIImage(named: "imageFilm1"), movieId: 1))
    }
}
